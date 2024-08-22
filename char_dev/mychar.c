#include <linux/types.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>

#define MY_CHAR_NAME "my_dev"
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

static ssize_t my_write(struct file *file, const char __user *buf,
    size_t lbuf, loff_t *ppos)
{
    return 0;
}

static loff_t my_lseek(struct file *file, loff_t offset, int orig) 
{
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,
    size_t lbuf, loff_t *ppos)
{
    return 0;
}

static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
    .llseek = my_seek
};

static int __init my_inint(void)
{
    int ret;

    misc_dev.name = "MY_CHAR_NAME";
    misc_dev.minor = MISC_DYNAMIC_MINOR;
    misc_dev.fops = &my_fops;
    misc_dev.mode = 0660;
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
