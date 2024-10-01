#include <linux/types.h>
#include <linux/module.h>
#include <linux/wait.h>
 #include <linux/poll.h>
 
static unsigned int epoll_poll(struct file *file, poll_table *wait)
{
    return 0;
}

static int epoll_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int epoll_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static const struct file_operations epoll_fops = {
    .owner = THIS_MODULE,
    .open = epoll_open,
    .release = epoll_release,
    .poll = epoll_poll
};

static int __init epoll_init(void)
{
    return 0;
}

static void __exit epoll_exit(void)
{
}

module_init(epoll_init);
module_exit(epoll_exit);

MODULE_LICENSE("Dual BSD/GPL");
