PWD = $(shell pwd)
INCLUDE = $(PWD)/include
USR_INCLUDE = $(PWD)/usr/include
QEMU = qemu-system-riscv32
QEMUFLAGS = -machine virt -bios default -kernel build/kernel
QEMUPIDFILE = ./qemu.pid
CC = clang
CFLAGS = -std=c11 -O0 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
				 -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib \
				 -I $(INCLUDE)
USRCFLAGS = -std=c11 -O0 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
            -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib \
            -I $(USR_INCLUDE)
USR_C_SRC = $(shell find usr/src -name "*.c")
USR_ASM_SRC = $(shell find usr/src -name "*.S")
USR_STD = usr/src/console.c usr/src/user.S
C_SRC = $(shell find src -name "*.c")
ASM_SRC = $(shell find src -name "*.S")
SRC = $(C_SRC) $(ASM_SRC)
usr/bin/%.elf: usr/src/%.c usr/src/console.c usr/src/user.S usr/user.ld
	$(CC) $(USRCFLAGS) -Wl,-Tusr/user.ld -Wl,-Map=usr/user.map -o $@ $< $(USR_STD)
usr/bin/%.bin: usr/bin/%.elf
	llvm-objcopy --set-section-flags .bss=alloc,contents -O binary $< $@
usr/bin/%.bin.o: usr/bin/%.bin
	llvm-objcopy -Ibinary -Oelf32-littleriscv $< $@
build/kernel: $(SRC) usr/bin/init.bin.o usr/bin/sh.bin.o src/kernel/kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tsrc/kernel/kernel.ld -Wl,-Map=build/kernel.map \
		-o $@ $(SRC) usr/bin/init.bin.o usr/bin/sh.bin.o
clean:
	rm -rf build/* usr/bin/* usr/user.map
qemu_debug: build/kernel
	$(QEMU) $(QEMUFLAGS) -s -S -display sdl -daemonize -monitor none -pidfile $(QEMUPIDFILE)
run: build/kernel
	$(QEMU) $(QEMUFLAGS) -display sdl -monitor none --no-reboot
report:
	typst compile doc/informe.typ doc/informe.pdf
	
debug: qemu_debug
	gdb build/kernel \
	-ex "target remote localhost:1234" \
	-ex "set confirm off" \
	-ex "monitor system_reset" \
	-ex "b boot" \
	-ex "c" \
	-ex "source .gdbconfig"

