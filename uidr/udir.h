#ifndef UIDR_H
#define UIDR_H

#include <pthread.h>

struct uida {
    u32 min;
    u32 max;
    pthread_spinlock_t lock;

    u32 index;  /* Cache the latest successfully allocated index */

    u32 num;    /* Num of bits */
    unsigned long *bits;
};

int uida_alloc(struct uida *ida, u32 *id);
void uida_free(struct uida *ida, u32 id);

/* Alloc range. [min, max] */
int uida_init(struct uida *ida, u32 min, u32 max);
void uida_destroy(struct uida *ida);

#define likely(x)           __builtin_expect(!!(x), 1)
#define unlikely(x)         __builtin_expect(!!(x), 0)

#endif
