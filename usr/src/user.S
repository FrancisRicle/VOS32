.section .text.start
.globl start
start:
  la sp, __stack_top
  call main
  call exit
.section .text
.globl syscall
syscall:
  ecall
  ret
.globl exit
exit:
  li a0, 3
  call syscall
  ret
