cmd_arch/x86/boot/compressed/kernel_info.o := gcc -Wp,-MMD,arch/x86/boot/compressed/.kernel_info.o.d -nostdinc -isystem /usr/lib64/gcc/x86_64-unknown-linux-gnu/14.2.1/include -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -m32 -O2 -std=gnu11 -fno-strict-aliasing -fPIE -Wundef -DDISABLE_BRANCH_PROFILING -march=i386 -mno-mmx -mno-sse -ffreestanding -fshort-wchar -fno-stack-protector -Wno-address-of-packed-member -Wno-pointer-sign -fmacro-prefix-map=./= -fno-asynchronous-unwind-tables -D__DISABLE_EXPORTS -Wa,-mrelax-relocations=no -include ./include/linux/hidden.h -D__ASSEMBLY__    -c -o arch/x86/boot/compressed/kernel_info.o arch/x86/boot/compressed/kernel_info.S

source_arch/x86/boot/compressed/kernel_info.o := arch/x86/boot/compressed/kernel_info.S

deps_arch/x86/boot/compressed/kernel_info.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  include/linux/hidden.h \
  arch/x86/include/uapi/asm/bootparam.h \

arch/x86/boot/compressed/kernel_info.o: $(deps_arch/x86/boot/compressed/kernel_info.o)

$(deps_arch/x86/boot/compressed/kernel_info.o):
