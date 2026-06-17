QEMU = qemu-system-riscv32
QEMUFLAGS = -machine virt -bios ./opensbi.bin -kernel kernel-bin
QEMUPIDFILE = ./qemu.pid
CC = clang
CFLAGS = -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
				 -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib
SRCS = kernel/kernel.c kernel/kernel.S traps/traps.S lib/libc.c mmu/mmu.c scheduler/scheduler.c scheduler/scheduler.S
kernel-bin: $(SRCS) kernel/kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tkernel/kernel.ld -Wl,-Map=kernel.map \
		-o $@ $(SRCS)
clean:
	rm -rf kernel/kernel kernel.map $(QEMUPIDFILE)
qemu_debug: kernel-bin
	$(QEMU) $(QEMUFLAGS) -s -S -display sdl -daemonize -monitor none -pidfile $(QEMUPIDFILE)
run: kernel-bin
	$(QEMU) $(QEMUFLAGS) -display sdl -monitor none --no-reboot
report:
	typst compile doc/informe.typ doc/informe.pdf
	
debug: qemu_debug
	gdb kernel-bin -ex "target remote localhost:1234" -ex "set confirm off" -ex "monitor system_reset" -ex "c" -ex "source .gdbconfig"

