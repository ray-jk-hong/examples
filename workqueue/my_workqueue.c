#include <linux/types.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/printk.h>

struct workqueue_struct *g_wq;
struct delayed_work g_work;

static void my_work(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    pr_info("My work scheduled\n");
    queue_delayed_work(g_wq, dwork, msecs_to_jiffies(2000));
}

static int __init my_wq_init(void)
{
    g_wq = alloc_workqueue("my_wq", 0, 0);
    if (!g_wq) {
        pr_err("Create workqueue fail.\n");
        return -ENOMEM;
    }
    INIT_DELAYED_WORK(&g_work, my_work);
    queue_delayed_work(g_wq, &g_work, 0);
    return 0;
}

static void __exit my_wq_exit(void)
{
    cancel_delayed_work_sync(&g_work);
    destroy_workqueue(g_wq);
}

module_init(my_wq_init);
module_exit(my_wq_exit);

MODULE_LICENSE("Dual BSD/GPL");
