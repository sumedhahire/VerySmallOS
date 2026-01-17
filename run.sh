#!/bin/bash
set -xue

# qemu file path
QEMU=qemu-system-riscv32

# OpenSBI firmware (riscv32)
OPENSBI=/usr/lib/riscv32-linux-gnu/opensbi/generic/fw_dynamic.bin

# start qemu
$QEMU \
  -machine virt \
  -bios $OPENSBI \
  -nographic \
  -serial mon:stdio \
  --no-reboot

