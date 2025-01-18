#ifndef MDEV_BUS_H
#define MDEV_BUS_H

#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/printk.h>

int __init mdev_bus_init(void);
void __exit mdev_bus_uninit(void);
struct bus_type *mdev_get_bus_type(void);

#endif