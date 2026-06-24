PWD = $(shell pwd)
INCLUDE = $(PWD)/include
QEMU = qemu-system-riscv32
QEMUFLAGS = -machine virt -bios ./opensbi.bin -kernel kernel-bin
QEMUPIDFILE = ./qemu.pid
CC = clang
CFLAGS = -std=c11 -O0 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
				 -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib \
				 -I $(INCLUDE)
CSRC = $(shell find src -name "*.c")
SSRC = $(shell find src -name "*.S")
SRCS = $(CSRC) $(SSRC)
kernel-bin: $(SRCS) src/kernel/kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tsrc/kernel/kernel.ld -Wl,-Map=kernel.map \
		-o $@ $(SRCS)
clean:
	rm -rf kernel-bin kernel.map
qemu_debug: kernel-bin
	$(QEMU) $(QEMUFLAGS) -s -S -display sdl -daemonize -monitor none -pidfile $(QEMUPIDFILE)
run: kernel-bin
	$(QEMU) $(QEMUFLAGS) -display sdl -monitor none --no-reboot
report:
	typst compile doc/informe.typ doc/informe.pdf
	
debug: qemu_debug
	gdb kernel-bin \
	-ex "target remote localhost:1234" \
	-ex "set confirm off" \
	-ex "monitor system_reset" \
	-ex "b kmain" \
	-ex "c" \
	-ex "source .gdbconfig"

