obj-m += hello-driver.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


#Fonte do código: https://medium.com/dvt-engineering/how-to-write-your-first-linux-kernel-module-cf284408beeb
