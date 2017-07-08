obj-m += chardev.o

KDIR = /usr/src/linux-headers-4.8.0-58-generic


all:
	 $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	 
clean:
		rm -f *.o *.ko *.mod.* *.symvers *.order
