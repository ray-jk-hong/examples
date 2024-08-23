KERN_DIR?= /lib/modules/$(shell uname -r)/build

ifneq ($(KERNELRELEASE),)
	obj-m := my_debugfs.o
    EXTRA_CFLAGS+=-I${PWD}
else
	PWD := $(shell pwd)

defulat:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
endif

clean:
	make -C $(KERN_DIR) M=$(PWD) clean

