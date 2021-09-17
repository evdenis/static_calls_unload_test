KDIR=/lib/modules/$(shell uname -r)/build

obj-m := static_calls1.o static_calls2.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean


