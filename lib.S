.section .text
.globl kputc

# kputc(char c) -> a0 contiene el caracter
kputc:
    li a7, 1          # SBI console_putchar
    ecall
    ret

.section .text.boot
.globl boot
boot:
    la sp, __stack_top
    j kmain           # Saltamos al C
