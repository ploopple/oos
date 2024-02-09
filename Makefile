CC = gcc

CFLAGS = \
	-pedantic \
	-fno-builtin \
	-nostdlib \
	-O2 \
	-g \
	-ffreestanding \
	-Wall \
	-Wextra \
	-Werror \
	-m32 \
	-fno-exceptions \
	-fno-leading-underscore \
	-std=gnu99 \
	-fstack-protector-strong \
	-fstack-clash-protection \
	-fpie -Wl,-pie \
	-D_FORTIFY_SOURCE=2 \
	-Werror=implicit-function-declaration \
	-static \
	-c


OBJS = \
	build/boot.o \
	build/kernel.o \
	build/crti.o \
	build/tty.o \
	build/crtn.o \
	build/port.o \
	build/vga.o 

.PHONY: all clean build r d docker-build docker-run lldb

all: clean build

clean:
	rm -rf build/*

build:
	as -g --32 src/kernel/arch/x86/boot.s -o build/boot.o
	as -g --32 src/kernel/arch/x86/crti.s -o build/crti.o
	as -g --32 src/kernel/arch/x86/crtn.s -o build/crtn.o
	$(CC) $(CFLAGS) src/kernel/kernel.c -o build/kernel.o
	$(CC) $(CFLAGS) src/kernel/vga.c -o build/vga.o
	$(CC) $(CFLAGS) src/kernel/tty.c -o build/tty.o
	$(CC) $(CFLAGS) src/kernel/port.c -o build/port.o
	ld -T src/kernel/arch/x86/linker.ld -m elf_i386 -o build/os $(OBJS) 

r: build/os
	qemu-system-i386 -full-screen -kernel build/os

d: build/os
	qemu-system-i386 -s -S -kernel build/os

docker-build: Dockerfile
	docker build -t os .

docker-run: Dockerfile
	docker run -it -v .:/os os

gdb: build/os
	gdb build/os -ex "target remote host.docker.internal:1234"
