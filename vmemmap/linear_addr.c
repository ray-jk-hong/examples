#include <stdio.h>

#include "linear_addr.h"

#define CONFIG_ARM64_VA_BITS    48
#define VA_BITS                 (CONFIG_ARM64_VA_BITS)
#define VA_BITS_MIN             48

#define _PAGE_END(va)           (-(UL(1) << ((va) - 1)))

#define PAGE_SHIFT              12 // 4KB page size
#define _PAGE_OFFSET(va)        (-(UL(1) << (va)))
#define PAGE_OFFSET             (_PAGE_OFFSET(VA_BITS))

#define MODULES_VSIZE       (2 * 1024 * 1024 * 1024) // 2GB
#define MODULES_VADDR       (_PAGE_END(VA_BITS_MIN))
#define MODULES_END     (MODULES_VADDR + MODULES_VSIZE)

// sizeof(struct page) = 64
// order_base_2(64) = 6
// #define STRUCT_PAGE_MAX_SHIFT   (order_base_2(sizeof(struct page)))
#define STRUCT_PAGE_MAX_SHIFT   6
#define VMEMMAP_SHIFT           (PAGE_SHIFT - STRUCT_PAGE_MAX_SHIFT)

#define VMEMMAP_START           (-(UL(1) << (VA_BITS - VMEMMAP_SHIFT)))
#define VMEMMAP_SIZE            ((_PAGE_END(VA_BITS_MIN) - PAGE_OFFSET) >> VMEMMAP_SHIFT)
#define VMEMMAP_END             (VMEMMAP_START + VMEMMAP_SIZE)

#define FIXADDR_TOP             ((VMEMMAP_START - (32 * 1024 * 1024)))

int main(int argc, char *argv[])
{
    printf("PAGE_OFFSET=0x%lx\n", PAGE_OFFSET);
    printf("VMEMMAP_START=0x%lx\n", VMEMMAP_START);
    printf("VMEMMAP_SIZE=0x%lx\n", VMEMMAP_SIZE);
    printf("FIXADDR_TOP=0x%lx\n", FIXADDR_TOP);

    return 0;
}
