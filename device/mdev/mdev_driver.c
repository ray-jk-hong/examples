#include "mdev.h"
#include "mdev_bus.h"
#include "mdev_driver.h"

static struct mdev_driver mdev_drv;

int __init mdev_drv_init(void)
{
    int ret;

    mdev_drv.driver.bus = mdev_get_bus_type();
    ret = driver_register(&mdev_drv.driver);
    if (ret != 0) {
        pr_err("Drv register fail\n");
        return ret;
    }

    return 0;
}

void __exit mdev_drv_uninit(void) 
{
    driver_unregister(&mdev_drv.driver);
}

MODULE_LICENSE("GPL");
