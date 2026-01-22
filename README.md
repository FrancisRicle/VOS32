# VOS32
RISC-V 32 bit bitss Kernel
------------------
Vamos a usar `Open SBI` como implementacion de la RISC-V Supervisor Binary Interface

## Dependencias
* `llvm`
* `lld`
* `clang`
* `qemu-system-riscv32`
* `curl`
* `docker` (opcional, con docker las dependencias anterior no hacen falta)

## Como usar
- Con docker: `make docker_build` despues `make docker_run`
- Sin docker: `make qemu`
