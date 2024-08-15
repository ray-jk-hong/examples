#include <linux/types.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/workqueue.h>

static struct workqueue_struct *wq;
static struct work_struct work;

static void charDev_work(struct work_struct *work)
{
    pr_info("charDev work start\n");
}

static int __init charDev_init(void)
{
    int ret;

    wq = alloc_workqueue("xxx_wq", WQ_MEM_RECLAIM | WQ_FREEZABLE | WQ_UNBOUND | WQ_SYSFS, 0);
    if (!wq) {
        return -ENOMEM;
    }
    INIT_WORK(&work, charDev_work);

    queue_work(wq, &work);
    pr_info("charDev init\n");

    return 0;
}

static void __exit charDev_exit(void)
{
    pr_info("charDev exit\n");
    destroy_workqueue(wq);
}

module_init(charDev_init);
module_exit(charDev_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Ray.jk.hong");

