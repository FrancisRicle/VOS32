QEMU = qemu-system-riscv32
QEMUFLAGS = -machine virt -bios ./opensbi.bin -kernel kernel
QEMUPIDFILE = ./qemu.pid
CC = clang
CFLAGS = -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
				 -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib
SRCS = kernel.c kernel.S traps.S libc.c
kernel: $(SRCS) kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tkernel.ld -Wl,-Map=kernel.map \
		-o $@ $(SRCS)
clean:
	rm -rf kernel kernel.map $(QEMUPIDFILE) *.out *.log *.toc *.aux
qemu_debug: kernel
	$(QEMU) $(QEMUFLAGS) -s -S -display sdl -daemonize -monitor none -pidfile $(QEMUPIDFILE)
run: kernel
	$(QEMU) $(QEMUFLAGS) -display sdl -monitor none --no-reboot
report:
	typst compile doc/informe.typ informe.pdf
	
debug: qemu_debug
	gdb kernel -ex "target remote localhost:1234" -ex "set confirm off" -ex "b init_traps" -ex "monitor system_reset" -ex "c" -ex "source gdbconfig"

