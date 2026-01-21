FROM debian:13.3

RUN apt-get update && apt-get install -y \
    make \
    curl \
    tar \
    build-essential \
    clang \
    llvm \
    lld \
    qemu-system-riscv32 \
    curl

COPY . .
CMD ["make", "qemu"]


