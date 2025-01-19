#include "mdev.h"
#include "mtty.h"
#include "mdev_bus.h"
#include "mdev_device.h"

static struct mdev_device mdev_dev;

static void mdev_dev_release(struct device *dev)
{
	dev_dbg(dev, "mtty: released\n");
}

static int mdev_dev_register(void)
{
    int ret;

    memset(&mdev_dev, 0, sizeof(mdev_dev));
    device_initialize(&mdev_dev.dev);
    mdev_dev.dev.parent = mtty_get_dev();
    mdev_dev.dev.bus = mdev_get_bus_type();
    mdev_dev.dev.release = mdev_dev_release;
    dev_set_name(&mdev_dev.dev, "my_mdev");
    ret = device_add(&mdev_dev.dev);
    if (ret != 0) {
        pr_err("Device add fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}

static void mdev_dev_unregister(void)
{
    device_unregister(&mdev_dev.dev);
}

static int mdev_dev_create(void)
{
    return 0;
}

static void mdev_dev_destroy(void)
{
}


int mdev_dev_init(void)
{
    int ret;

    ret = mdev_dev_register();
    if (ret != 0) {
        pr_err("Mdev dev register fail. (ret=%d)\n", ret);
        return ret;
    }

    ret = mdev_dev_create();
     if (ret != 0) {
        mdev_dev_unregister();
        pr_err("Mdev dev create fail. (ret=%d)\n", ret);
        return ret;
    }

    pr_info("Dev init\n");
    return 0;
}

void mdev_dev_uninit(void) 
{
    pr_info("Dev uninit\n");
    mdev_dev_destroy();
    mdev_dev_unregister();
}

MODULE_LICENSE("GPL");