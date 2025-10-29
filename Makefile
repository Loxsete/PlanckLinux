CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -std=c11
QEMU    := qemu-system-i386
NPROC   := $(shell nproc)

all: linux bsh hello initramfs grub

linux:
	$(MAKE) -C linux CC="gcc -std=gnu89" -j$(NPROC)
	cp linux/arch/x86/boot/bzImage hdd/boot/vmlinuz

bsh:
	if [ ! -d bsh ]; then \
		git clone https://github.com/GNUfault/bsh.git; \
	fi
	$(MAKE) -C bsh
	mkdir -p initramfs/bin
	cp bsh/bsh initramfs/bin/
	cp bsh/cmds/* initramfs/bin/ 2>/dev/null || true

hello:
	$(MAKE) -C hello
	mkdir -p initramfs/bin
	cp hello/hello initramfs/bin/hello

initramfs: bsh hello
	rm -f hdd/boot/initramfs.cpio
	cd initramfs && \
	find . -print | cpio -H newc -o > ../hdd/boot/initramfs.cpio && \
	cd ..

grub:
	grub-mkrescue -o linux.iso hdd

run: all
	$(QEMU) -cdrom linux.iso -m 512M -serial stdio

clean:
	-$(MAKE) -C linux clean
	-$(MAKE) -C bsh clean
	-$(MAKE) -C hello clean
	rm -rf initramfs/bin/*
	rm -f hdd/boot/vmlinuz hdd/boot/initramfs.cpio
	rm -f linux.iso

.PHONY: all linux bsh hello initramfs grub run clean
