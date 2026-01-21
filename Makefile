QEMU = qemu-system-riscv32
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
	rm -rf kernel kernel.map
qemu: kernel
		$(QEMU) -machine virt \
			-bios ./opensbi.bin \
			-nographic \
			-serial mon:stdio --no-reboot \
    	-kernel kernel
	

