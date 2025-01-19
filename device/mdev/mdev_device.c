#include "mdev.h"
#include "mdev_bus.h"
#include "mdev_device.h"

static struct mdev_device mdev_dev;

int mdev_dev_init(void)
{
    int ret;

    device_initialize(&mdev_dev.dev);
    mdev_dev.dev.bus = mdev_get_bus_type();
    ret = dev_set_name(&mdev_dev.dev, "my_mdev");
    if (ret != 0) {
        pr_err("Set name fail. (ret=%d)\n", ret);
        return ret;
    }

    ret = device_add(&mdev_dev.dev);
    if (ret != 0) {
        pr_err("Device add fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}

void mdev_dev_uninit(void) 
{
    device_del(&mdev_dev.dev);
}

MODULE_LICENSE("GPL");