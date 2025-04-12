#include <linux/types.h>
#include <linux/module.h>
#include <linux/blkdev.h>

#define MAX_DEV_NUM 1
#define BLKDEV_NAME "blkdev"
#define BLKDEV_MINOR    0

struct blkdev {
    int major;
    dev_t devt;
    struct gendisk *gd;
    struct  request_queue *queue;
} g_blkdev;

static int _blkdev_init(struct blkdev *blkdev)
{
    dev_t devt;
    int ret;

    ret = alloc_chrdev_region(&devt, 0, MAX_DEV_NUM, BLKDEV_NAME);
    if (ret != 0) {
        return ret;
    }

    ret = register_blkdev(MAJOR(devt), BLKDEV_NAME);
    if (ret != 0) {
        unregister_chrdev_region(MKDEV(devt, 0), MAX_DEV_NUM);
        return ret;
    }
    blkdev->devt = devt;
    blkdev->major = MAJOR(devt); 
    return 0;
}

static void _blkdev_uninit(struct blkdev *blkdev)
{
    unregister_blkdev(blkdev->major, BLKDEV_NAME);
    unregister_chrdev_region(blkdev->devt, MAX_DEV_NUM);
}

static int blkdev_gd_init(struct blkdev *blkdev)
{
    return 0;
}

static void blkdev_gd_uninit(struct blkdev *blkdev)
{

}

static int __init blkdev_init(void)
{
    int ret;

    ret = _blkdev_init(&g_blkdev);
    if (ret != 0) {
        return ret;
    }

    ret = blkdev_gd_init(&g_blkdev);
    if (ret != 0) {
        _blkdev_uninit(&g_blkdev);
        return ret;
    }

    return 0;
}

static void __exit blkdev_exit(void)
{
    blkdev_gd_uninit(&g_blkdev);
    _blkdev_uninit(&g_blkdev);
}

module_init(blkdev_init);
module_exit(blkdev_exit);

MODULE_LICENSE("Dual BSD/GPL");
