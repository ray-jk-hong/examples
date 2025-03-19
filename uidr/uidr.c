#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "uidr.h"

#define IDR_BITS_PER_BYTE           8
#define IDR_BITS_PER_LONG           (sizeof(long) * IDR_BITS_PER_BYTE)
#define IDA_BITS_PER_TYPE(type)     (sizeof(type) * IDR_BITS_PER_BYTE)
#define IDA_BITS_TO_LONGS(nr)       DIV_ROUND_UP(nr, IDA_BITS_PER_TYPE(long))

static int uida_lock_init(struct uida *ida)
{
    return pthread_spin_init(&ida->lock, PTHREAD_PROCESS_PRIVATE);
}

static void uida_lock_uninit(struct uida *ida)
{
    (void)pthread_spin_destroy(&ida->lock);
}

static void uida_lock(struct uida *ida)
{
    (void)pthread_spin_lock(&ida->lock);
}

static void uida_unlock(struct uida *ida)
{
    (void)pthread_spin_unlock(&ida->lock);
}

static int uida_alloc_locked(struct uida *ida, u32 *id)
{
    u32 index = ida->index; /* Get the latest successfully allocated index */
    u32 i;

    if (unlikely(ida->bits == NULL)) {
        return EINVAL;
    }

    for (i = 0; i < ida->num; i++) {
        u32 new_index = (index + i) % ida->num;
        int offset = ffsl((long int)~ida->bits[new_index]);
        if (offset == 0) {
            continue;
        }
        offset--;
        ida->bits[new_index] |= 1UL << offset;
        *id = new_index * (u32)IDR_BITS_PER_LONG + (u32)offset + ida->min;
        ida->index = new_index; /* Set to cached index */
        return 0;
    }

    return ENOSPC;
}

int uida_alloc(struct uida *ida, u32 *id)
{
    int ret;

    if (unlikely((ida == NULL) || (id == NULL))) {
        return EINVAL;
    }

    uida_lock(ida);
    ret = uida_alloc_locked(ida, id);
    uida_unlock(ida);

    return ret;
}

static void uida_free_locked(struct uida *ida, u32 id)
{
    u32 index, offset;
    u32 id_space;

    if (unlikely((id < ida->min) || (id > ida->max))) {
        return;
    }
    id_space = id - ida->min;
    index = id_space / IDR_BITS_PER_LONG;
    offset = id_space % IDR_BITS_PER_LONG;
    ida->bits[index] &= ~(1UL << offset);
}

void uida_free(struct uida *ida, u32 id)
{
    if (likely(ida != NULL)) {
        uida_lock(ida);
        uida_free_locked(ida, id);
        uida_unlock(ida);
    }
}

static int uida_init_locked(struct uida *ida, u32 min, u32 max)
{
    unsigned long *bits = NULL;
    u32 offset;
    u32 num, i;

    if (unlikely(min > max)) {
        return EINVAL;
    }
    num = IDA_BITS_TO_LONGS(max - min + 1);
    bits = (unsigned long *)calloc(num, sizeof(unsigned long));
    if (unlikely(bits == NULL)) {
        return ENOMEM;
    }
    ida->num = num;
    ida->bits = bits;

    offset = (max - min + 1) % IDR_BITS_PER_LONG;
    if (offset != 0) {
        for (i = offset; i < IDR_BITS_PER_LONG; i++) {
            /* Set remain bit */
            bits[num - 1] |= 1UL << i;
        }
    }
    ida->min = min;
    ida->max = max;

    return 0;
}

static void uida_uninit(struct uida *ida)
{
    if (likely(ida->bits != NULL)) {
        free(ida->bits);
        ida->bits = NULL;
    }
}

int uida_init(struct uida *ida, u32 min, u32 max)
{
    int ret;

    ret = uida_lock_init(ida);
    if (unlikely(ret != 0)) {
        return ret;
    }
    uida_lock(ida);
    ret = uida_init_locked(ida, min, max);
    uida_unlock(ida);
    if (unlikely(ret != 0)) {
        uida_lock_uninit(ida);
        return ret;
    }

    return 0;
}

void uida_destroy(struct uida *ida)
{
    uida_lock(ida);
    uida_uninit(ida);
    uida_unlock(ida);
    uida_lock_uninit(ida);
}
