KERN_DIR = /Users/hong/study/codes/linux/linux-6.6.42

ifneq ($(KERNELRELEASE),)
	obj-m := charDev.o
    EXTRA_CFLAGS+=-I${PWD}
else
	PWD := $(shell pwd)
defulat:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
endif

clean:
	make -C $(KERN_DIR) M=$(PWD) clean

