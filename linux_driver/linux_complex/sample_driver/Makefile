#generate the path
CURRENT_PATH:=$(shell pwd)
#the absolute path
LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build

#complie object
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

obj-m +=sample_driver.o