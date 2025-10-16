all: linux bsh hello initramfs grub

linux:
	make -C linux -j$(nproc)
	cp linux/arch/x86/boot/bzImage hdd/boot

bsh:
        git clone --depth https://github.com/GNUfault/bsh.git
	make -C bsh
	cp bsh/bsh initramfs/bin

hello:
	make -C hello
	cp hello/hello initramfs/bin

initramfs:
	rm -f hdd/boot/initramfs.cpio
	cd initramfs && \
        find . | cpio -H newc -o > ../hdd/boot/initramfs.cpio && \
	cd ..

grub:
	grub-mkrescue -o linux.iso hdd

run:
	qemu-system-i386 -cdrom linux.iso

.PHONY: linux bsh hello initramfs grub run
