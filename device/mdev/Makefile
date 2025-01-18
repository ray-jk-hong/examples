KERN_DIR?= /lib/modules/$(shell uname -r)/build

ifneq ($(KERNELRELEASE),)
	obj-m := mdev.o
	mdev-y += mdev.o mdev_bus.o mdev_driver.o
    EXTRA_CFLAGS+=-I${PWD}
else
	PWD := $(shell pwd)
defulat:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
endif

clean:
	make -C $(KERN_DIR) M=$(PWD) clean

