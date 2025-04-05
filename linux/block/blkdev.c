#include <linux/types.h>
#include <linux/module.h>

static int __init blkdev_init(void)
{
    return 0;
}

static void __exit blkdev_exit(void)
{
}

module_init(blkdev_init);
module_exit(blkdev_exit);

MODULE_LICENSE("Dual BSD/GPL");
