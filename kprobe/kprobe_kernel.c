#include <linux/types.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kprobes.h>

static char symbol[64] = "kernel_clone";

static struct kprobe kp = {
    .symbol_name = symbol
};

static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    pr_info("<%s> pre_handler: p->addr=0x%p\n", 
        p->symbol_name, p->addr);
    return 0;
}

static void __kprobes handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    pr_info("<%s> post_handler: p->addr=0x%p\n", 
        p->symbol_name, p->addr);
}

static int __init poll_init(void)
{
    int ret;

    kp.pre_handler = handler_pre;
    kp.post_handler = handler_post;
    ret = register_kprobe(&kp);
    if (ret != 0) {
        pr_err("Register kprobe fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}

static void __exit poll_exit(void)
{
    unregister_kprobe(&kp);
}

module_init(poll_init);
module_exit(poll_exit);
MODULE_LICENSE("Dual BSD/GPL");
