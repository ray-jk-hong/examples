#include "mdev_bus.h"

static int bus_probe(struct device *dev)
{
    pr_info("bus probe\n");
    return 0;
}

static void bus_remove(struct device *dev)
{
    pr_info("bus remove\n");
}

static int bus_match(struct device *dev, struct device_driver *drv)
{
    pr_info("bus match\n");
    return 0;
}

static struct bus_type mdev_bus_type = {
    .name = "my_bus",
    .probe = bus_probe,
    .remove = bus_remove,
    .match = bus_match
};

struct bus_type *mdev_get_bus_type(void)
{
    return &mdev_bus_type;
}

int mdev_bus_init(void)
{
    int ret;

    ret = bus_register(&mdev_bus_type);
    if (ret != 0) {
        pr_err("Bus register fail. (ret=%d)\n", ret);
        return ret;
    }
    pr_info("Bus init\n");
    return 0;

}

void mdev_bus_uninit(void) 
{
    pr_info("Bus uninit\n");
    bus_unregister(&mdev_bus_type);
}

MODULE_LICENSE("GPL");
