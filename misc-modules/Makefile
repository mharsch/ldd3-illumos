#CC = 		/opt/SUNWspro/sunstudio12.1/bin/cc
CC = 		/usr/bin/gcc
LD =		/usr/ccs/bin/ld
STUDIO_FLAGS =	-D_KERNEL -m64 -xmodel=kernel
GCC_FLAGS =	-D_KERNEL -m64 -mcmodel=kernel -mno-red-zone -ffreestanding \
		-nodefaultlibs

#CFLAGS =	$(STUDIO_FLAGS)
CFLAGS =	$(GCC_FLAGS)

DEBUG_FLAGS =	-DDEBUG

all: hello hellop

hello.o:
	$(CC) $(CFLAGS) -c -o hello.o hello.c

hellop.o:
	$(CC) $(CFLAGS) -c -o hellop.o hellop.c

hello: hello.o
	$(LD) -r -o hello hello.o

hellop: hellop.o
	$(LD) -r -o hellop hellop.o

clean:
	-rm -f hello*.o hello hellop

install:
	sudo cp hello.conf /usr/kernel/drv
	sudo cp hellop.conf /usr/kernel/drv
	cp hello /tmp
	cp hellop /tmp
	-sudo ln -s /tmp/hello /usr/kernel/drv/amd64/hello
	-sudo ln -s /tmp/hellop /usr/kernel/drv/amd64/hellop

clobber: clean
	-sudo rm /usr/kernel/drv/amd64/hello*
	-rm /tmp/hello*
