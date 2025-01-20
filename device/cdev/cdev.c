#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/printk.h>

#define MAX_DEV_NUM 16U

struct cdev g_cdev[MAX_DEV_NUM];
struct device *g_dev[MAX_DEV_NUM];

static struct class *cdev_class;
static int cdev_major;

static int cdev_open(struct inode *inode, struct file *file) 
{
    int minor = iminor(inode);
    printk(KERN_INFO "Open cdev. (minor=%d)\n", minor);
    return 0;
}

static int cdev_release(struct inode *inode, struct file *file) 
{
    int minor = iminor(inode);
    printk(KERN_INFO "Release cdev. (minor=%d)\n", minor);
    return 0;
}

static ssize_t cdev_read(struct file *file, char __user *data, size_t size, loff_t *offset) 
{
    int minor = iminor(file_inode(file));
    printk(KERN_INFO "Read cdev. (minor=%d)\n", minor);
    return size;
}

static ssize_t cdev_write(struct file *file, const char __user *data, size_t size, loff_t *offset) 
{
    int minor = iminor(file_inode(file));
    printk(KERN_INFO "Write cdev. (iminor=%d)\n", minor);
    return size;
}

static struct file_operations g_cdev_fops = {
    .owner = THIS_MODULE,
    .open = cdev_open,
    .release = cdev_release,
    .read = cdev_read,
    .write = cdev_write
};

static char *_cdev_devnode(struct device *dev, umode_t *mode)
{
    return kasprintf(GFP_KERNEL, "my_cdev/%s", dev_name(dev));
}

static int _cdev_init(void)
{
    dev_t cdev_dev;
    int ret;

    cdev_class = class_create(THIS_MODULE, "my_cdev");
    if (cdev_class == NULL) {
        printk(KERN_ERR "Class create fail.\n");
        return -ENODEV;
    }
    cdev_class->devnode = _cdev_devnode;

    ret = alloc_chrdev_region(&cdev_dev, 0, MAX_DEV_NUM, "my_cdev");
    if (ret != 0) {
        class_destroy(cdev_class);
        cdev_class = NULL;
        printk(KERN_ERR "Alloc chardev region fail. (ret=%d).\n", ret);
        return ret;
    }
    cdev_major = MAJOR(cdev_dev);
    return 0;
}

static void _cdev_exit(void) 
{
    unregister_chrdev_region(MKDEV(cdev_major, 0), MAX_DEV_NUM);
    class_destroy(cdev_class);
    cdev_class = NULL;
}

static int _cdev_setup(int id)
{
    dev_t cdev_dev = MKDEV(cdev_major, id);
    int ret;

    cdev_init(&g_cdev[id], &g_cdev_fops);
    ret = cdev_add(&g_cdev[id], cdev_dev, 1);
    if (ret != 0) {
        printk(KERN_ERR "Cdev add fail. (ret=%d; id=%d).\n", ret, id);
        return ret;
    }
    g_dev[id] = device_create(cdev_class, NULL, cdev_dev, NULL, "my_cdev_%d", id);
    if (IS_ERR(g_dev[id])) {
        cdev_del(&g_cdev[id]);
        printk(KERN_ERR "Cdev add fail. (ret=%d; id=%d).\n", ret, id);
        return -EFAULT;
    }

    return 0;
}

static void _cdev_clean(int id)
{
    device_del(g_dev[id]);
    cdev_del(&g_cdev[id]);
}

static int cdev_setup(void)
{
    int i, j;

    for (i = 0; i < MAX_DEV_NUM; i++) {
        int ret = _cdev_setup(i);
        if (ret != 0) {
            printk(KERN_ERR "Alloc chardev region fail. (ret=%d).\n", ret);
            goto out;
        }
    }
    return 0;
out:
    for (j = 0; j < i; j++) {
        _cdev_clean(j);
    }
    return -EFAULT;
}

static void cdev_clean(void)
{
    int i;
    for (i = 0; i < MAX_DEV_NUM; i++) {
        _cdev_clean(i);
    }
}

static int __init cdev_mod_init(void)
{
    int ret;

    ret = _cdev_init();
    if (ret != 0) {
        printk(KERN_ERR "Cdev init fail. (ret=%d).\n", ret);
        return ret;
    }

    ret = cdev_setup();
    if (ret != 0) {
        _cdev_exit();
        printk(KERN_ERR "Cdev setup fail. (ret=%d).\n", ret);
        return ret;
    }

    return 0;
}

static void __exit cdev_mod_exit(void) 
{
    cdev_clean();
    _cdev_exit();
}

module_init(cdev_mod_init);
module_exit(cdev_mod_exit);
MODULE_LICENSE("GPL");
