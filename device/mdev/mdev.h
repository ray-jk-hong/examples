#ifndef MDEV_H
#define MDEV_H

#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/printk.h>

struct mdev_device {
    struct device dev;
};

struct mdev_driver {
    int (* probe)(struct mdev_device *dev);
    void (* remove)(struct mdev_device *dev);
    struct device_driver driver;
};

#endif