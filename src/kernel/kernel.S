.section .text.boot
.globl boot
boot:
    la sp, __stack_top
    j kmain           # Saltamos al C


.section .text



.globl halt
halt:
  wfi
  j halt

