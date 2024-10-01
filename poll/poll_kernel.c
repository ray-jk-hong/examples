#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>

static struct miscdevice misc_dev;

static DECLARE_WAIT_QUEUE_HEAD(poll_wq);

static int poll_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int poll_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static unsigned int poll_poll(struct file *file, poll_table *wait)
{
    int ret;

    return ret;
}

static const struct file_operations poll_fops = {
    .owner = THIS_MODULE,
    .open = poll_open,
    .release = poll_release,
    .poll = poll_poll,
};

static int __init poll_init(void)
{
    int ret;

    misc_dev.name = "poll_dev";
    misc_dev.minor = MISC_DYNAMIC_MINOR;
    misc_dev.fops = &poll_fops;
    misc_dev.mode = 0660;
    ret = misc_register(&misc_dev);
    if (ret != 0) {
        pr_err("Misc register fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}

static void __exit poll_exit(void)
{
    misc_deregister(&misc_dev);
}

module_init(poll_init);
module_exit(poll_exit);
MODULE_LICENSE("Dual BSD/GPL");
