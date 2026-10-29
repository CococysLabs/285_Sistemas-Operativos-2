obj-m += so2proc_seguro.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all clean load unload test
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
load: all
	sudo insmod so2proc_seguro.ko
unload:
	sudo rmmod so2proc_seguro
test: load
	echo 512 | sudo tee /proc/so2_monitor
	! echo 9999999999999999999999999999999999999999 | sudo tee /proc/so2_monitor
	$(MAKE) unload
