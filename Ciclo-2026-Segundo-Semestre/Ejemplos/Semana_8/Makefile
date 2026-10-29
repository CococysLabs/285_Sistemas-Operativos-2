obj-m += metricas.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all clean load unload
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
load: all
	sudo insmod metricas.ko
	dmesg | grep 'met:'
unload:
	sudo rmmod metricas
