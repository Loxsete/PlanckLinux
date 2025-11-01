CC := gcc
CFLAGS := -Wall -Wextra -O2 -std=c11 -m32 -static
QEMU := qemu-system-i386
NPROC := $(shell nproc)

all: linux bsh hello bsfetch initramfs grub

linux:
	$(MAKE) -C linux CC="gcc -std=gnu89" -j$(NPROC)
	cp linux/arch/x86/boot/bzImage hdd/boot/vmlinuz

bsh:
	if [ ! -d bsh ]; then \
		git clone https://github.com/Loxsete/bsh.git; \
	fi
	$(MAKE) -C bsh clean
	$(MAKE) -C bsh
	mkdir -p initramfs/bin
	cp bsh/bin/* initramfs/bin/
	cp bsh/bsh initramfs/bin/
	chmod +x initramfs/bin/*
	cd initramfs && \
		find . -print | cpio -H newc -o > ../hdd/boot/initramfs.cpio && \
		cd ..

hello:
	$(MAKE) -C hello || true
	mkdir -p initramfs/bin
	cp hello/hello initramfs/bin/hello
	cd initramfs && \
		find . -print | cpio -H newc -o > ../hdd/boot/initramfs.cpio && \
		cd ..

# ===============================
#  Добавлено: bsfetch (твой fastfetch)
# ===============================
bsfetch:
	@echo "==> Building bsfetch..."
	$(CC) $(CFLAGS) bsfetch/fetch.c -o bsfetch/bsfetch
	mkdir -p initramfs/bin
	cp bsfetch/bsfetch initramfs/bin/bsfetch
	chmod +x initramfs/bin/bsfetch
	cd initramfs && \
		find . -print | cpio -H newc -o > ../hdd/boot/initramfs.cpio && \
		cd ..
	@echo "==> bsfetch ready."

initramfs: bsh hello bsfetch
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
	rm -f bsfetch/bsfetch
	rm -f hdd/boot/vmlinuz hdd/boot/initramfs.cpio
	rm -f linux.iso

.PHONY: all linux bsh hello bsfetch initramfs grub run clean
