#!/bin/bash

clear

qemu-system-arm -kernel ./build/tecos_kernel-lab06.img -initrd ./build/tecos_kernel-lab06.img -m 128 -M raspi -serial stdio
