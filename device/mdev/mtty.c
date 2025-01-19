#include "mdev.h"
#include "mtty.h"

struct mtty_dev {
    struct class *mdev_class;
    dev_t devt;
    struct device dev;
} mtty_dev;

static void mtty_dev_release(struct device *dev)
{
	dev_dbg(dev, "mtty: released\n");
}

struct device *mtty_get_dev(void)
{
    return &mtty_dev.dev;
}

int mtty_init(void)
{
    int ret;

    mtty_dev.mdev_class = class_create(THIS_MODULE, "my_mtty_class");
    if (IS_ERR(mtty_dev.mdev_class)) {
        pr_err("Class create fail.");
        return -ENODEV;
    }

    mtty_dev.dev.class = mtty_dev.mdev_class;
    mtty_dev.dev.release = mtty_dev_release;
    dev_set_name(&mtty_dev.dev, "%s", "my_mtty_device");
    ret = device_register(&mtty_dev.dev);
    if (ret != 0) {
        class_destroy(mtty_dev.mdev_class);
        pr_err("Device register fail. (ret=%d)\n", ret);
        return ret;
    }
    pr_info("Mtty init\n");
    return 0;
}

void mtty_uninit(void)
{
    pr_info("Mtty uninit\n");
    device_unregister(&mtty_dev.dev);
    class_destroy(mtty_dev.mdev_class);
}

