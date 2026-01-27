QEMU = qemu-system-riscv32
QEMUFLAGS = -machine virt -bios ./opensbi.bin -kernel kernel
QEMUPIDFILE = ./qemu.pid
CC = clang
CFLAGS = -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
				 -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib
SRCS = kernel.c lib.S libc.c
docker_build:
	docker buildx build -t vos32 .
docker_run:
	docker run -it --rm vos32:latest
kernel: $(SRCS) kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tkernel.ld -Wl,-Map=kernel.map \
		-o $@ $(SRCS)
clean:
	rm -rf kernel kernel.map $(QEMUPIDFILE)
qemu_debug: kernel
	$(QEMU) $(QEMUFLAGS) -s -S -display sdl -daemonize -monitor none -pidfile $(QEMUPIDFILE)

run: kernel
	#$(QEMU) $(QEMUFLAGS) -nographic -serial mon:stdio --no-reboot
	$(QEMU) $(QEMUFLAGS) -display sdl -monitor none --no-reboot
	
debug: qemu_debug
	gdb kernel -ex "target remote localhost:1234" -ex "set confirm off" -ex "monitor system_reset" -ex "source gdbconfig"

