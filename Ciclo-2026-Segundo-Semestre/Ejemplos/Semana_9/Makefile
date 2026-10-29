obj-m += so2proc.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all clean load unload test
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
load: all
	sudo insmod so2proc.ko
unload:
	sudo rmmod so2proc
test: load
	cat /proc/so2_monitor
	echo 4096 | sudo tee /proc/so2_monitor
	! echo abc | sudo tee /proc/so2_monitor
	$(MAKE) unload
