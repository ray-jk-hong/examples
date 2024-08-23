#include <linux/types.h>
#include <linux/module.h>
#include <linux/debugfs.h>

static int my_debug_show(struct seq_file *m, void *private)
{
    seq_printf(m, "This is my debugfs\n");
    return 0;
}
DEFINE_SHOW_ATTRIBUTE(my_debug);

static struct dentry *g_root;

static int __init my_debugfs_init(void)
{
    g_root = debugfs_create_dir("my_debugfs", NULL);
    if (!g_root) {
        return -ENOMEM;
    }

    debugfs_create_file("show", 0444, g_root, NULL, &my_debug_fops);

    return 0;
}

static void __exit my_debugfs_exit(void)
{
    debugfs_remove(g_root);
}

module_init(my_debugfs_init);
module_exit(my_debugfs_exit);

MODULE_LICENSE("Dual BSD/GPL");
