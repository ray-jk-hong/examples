#include "mdev.h"
#include "mtty.h"
#include "mdev_bus.h"
#include "mdev_driver.h"
#include "mdev_device.h"

static int __init mdev_mod_init(void)
{
    int ret;

    ret = mdev_bus_init();
    if (ret != 0) {
        return ret;
    }

    ret = mdev_drv_init();
    if (ret != 0) {
        mdev_bus_uninit();
        return ret;
    }

    ret = mtty_init();
    if (ret != 0) {
        mdev_drv_uninit();
        mdev_bus_uninit();
        return ret;
    }

    ret = mdev_dev_init(); // 设备创建的时候调用
    if (ret != 0) {
        mtty_uninit();
        mdev_drv_uninit();
        mdev_bus_uninit();
        return ret;
    }

    pr_info("Mdev init\n");
    return 0;
}

static void __exit mdev_mod_exit(void) 
{
    pr_info("Mdev exit\n");
    mdev_dev_uninit();
    mtty_uninit();
    mdev_drv_uninit();
    mdev_bus_uninit();
}

module_init(mdev_mod_init);
module_exit(mdev_mod_exit);
MODULE_LICENSE("GPL");
