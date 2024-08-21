#include <linux/types.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>

static struct miscdevice misc_dev;

static int my_open(struct inode *inode, struct file *filp)
{
    pr_info("open\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
    pr_info("release\n");
    return 0;
}

static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release
};

static int __init my_inint(void)
{
    int ret;

    misc_dev.name = "my_dev";
    misc_dev.minor = MISC_DYNAMIC_MINOR;
    misc_dev.fops = &my_fops;
    misc_dev.mode = 0600;
    ret = misc_register(&misc_dev);
    if (ret != 0) {
        pr_err("Misc register fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}

static void __exit my_exit(void)
{
    misc_deregister(&misc_dev);
}

module_init(my_inint);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
