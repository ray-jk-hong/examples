#include <linux/types.h>
#include <linux/module.h>

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
