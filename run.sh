#!/bin/bash
set -xue

# qemu file path
QEMU=qemu-system-riscv32

# Path to clang and compiler flags
CC=clang  # Ubuntu users: use CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"
 
 # use c11
 # 02 use optimiation to generate efficint machine code
 # -g3 max amount of debug 
 # -Wall enable major warnings
 # Wextra enable additional warinings 
 # compile for 32-bit risv-v
 # ffreestanding - do not use host libs
 # fuse-ld=lld use llvm linker
 # fno-stack-protector disbale unnessary stack protection 
 #

# Build the kernel
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel_helloworld.c #change here for diff kernel

# OpenSBI firmware (riscv32)
OPENSBI=/usr/lib/riscv32-linux-gnu/opensbi/generic/fw_dynamic.bin

# start qemu
$QEMU \
  -machine virt \
  -bios $OPENSBI \
  -nographic \
  -serial mon:stdio \
  --no-reboot \
  -kernel kernel.elf

