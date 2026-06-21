.section .text
.globl exec
exec:
  mv sp, a1
  jalr ra, a0, 0x0
