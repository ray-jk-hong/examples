#include <linux/types.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/ioctl.h>

static int __init charDev_init(void)
{
    return 0;
}

static void __exit charDev_exit(void)
{
}

module_init(charDev_init);
module_exit(charDev_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("xxxx");

