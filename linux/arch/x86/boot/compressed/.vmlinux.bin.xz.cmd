cmd_arch/x86/boot/compressed/vmlinux.bin.xz := { cat arch/x86/boot/compressed/vmlinux.bin | sh ./scripts/xz_wrap.sh; printf \\220\\261\\032\\000; } > arch/x86/boot/compressed/vmlinux.bin.xz
