obj-m := hook.o 

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo rmmod hook; \
	sudo mkdir -p /lib/modules/$(KVERSION)/kernel/drivers/hook
	sudo cp hook.ko /lib/modules/$(KVERSION)/kernel/drivers/hook
	sudo depmod -a
	sudo modprobe hook