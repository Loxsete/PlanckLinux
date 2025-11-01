cmd_arch/x86/lib/atomic64_cx8_32.o := gcc -std=gnu89 -Wp,-MMD,arch/x86/lib/.atomic64_cx8_32.o.d -nostdinc -isystem /usr/lib64/gcc/x86_64-unknown-linux-gnu/14.2.1/include -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -m32    -c -o arch/x86/lib/atomic64_cx8_32.o arch/x86/lib/atomic64_cx8_32.S

source_arch/x86/lib/atomic64_cx8_32.o := arch/x86/lib/atomic64_cx8_32.S

deps_arch/x86/lib/atomic64_cx8_32.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  include/linux/linkage.h \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  include/linux/compiler_types.h \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
    $(wildcard include/config/MODULE_REL_CRCS) \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/TRIM_UNUSED_KSYMS) \
  arch/x86/include/asm/linkage.h \
    $(wildcard include/config/X86_32) \
    $(wildcard include/config/RETHUNK) \
    $(wildcard include/config/RETPOLINE) \
    $(wildcard include/config/SLS) \
  arch/x86/include/asm/alternative.h \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/MITIGATION_ITS) \
    $(wildcard include/config/STACK_VALIDATION) \
  include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  include/uapi/linux/types.h \
  arch/x86/include/generated/uapi/asm/types.h \
  include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/x86/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  arch/x86/include/asm/asm.h \
    $(wildcard include/config/KPROBES) \
  arch/x86/include/asm/extable_fixup_types.h \
  arch/x86/include/asm/bug.h \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  include/linux/instrumentation.h \
    $(wildcard include/config/DEBUG_ENTRY) \
  include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
    $(wildcard include/config/CFI_CLANG) \
  include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
  arch/x86/include/generated/asm/rwonce.h \
  include/asm-generic/rwonce.h \
  include/linux/once_lite.h \

arch/x86/lib/atomic64_cx8_32.o: $(deps_arch/x86/lib/atomic64_cx8_32.o)

$(deps_arch/x86/lib/atomic64_cx8_32.o):
