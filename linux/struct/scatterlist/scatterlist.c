#include <linux/types.h>
#include <linux/module.h>

static int __init scat_init(void)
{
    return 0;
}

static void __exit scat_exit(void)
{
}

module_init(scat_init);
module_exit(scat_exit);
MODULE_LICENSE("Dual BSD/GPL");
