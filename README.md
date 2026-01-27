# VOS32
RISC-V 32 bit bitss Kernel
------------------
Vamos a usar `Open SBI` como implementacion de la RISC-V Supervisor Binary Interface

## Dependencias
* `llvm`
* `lld`
* `clang`
* `sdl`
* `qemu-system-riscv32`
* `curl`
* `gdb`
* `gdb-multiarch`
* `docker` (opcional, con docker las dependencias anterior no hacen falta) TODAVIA NO ESTA LA IMAGEN LISTA

## Como usar
- Con docker: `make docker_build` despues `make docker_run` TODO
- Sin docker: `make qemu`
