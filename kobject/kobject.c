#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/printk.h>

static int __init kobject_mod_init(void)
{
    return 0;
}

static void __exit kobject_mod_exit(void) 
{
}

module_init(kobject_mod_init);
module_exit(kobject_mod_exit);
MODULE_LICENSE("GPL");
