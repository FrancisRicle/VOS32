.section .text.boot
.globl boot
boot:
    la sp, __stack_top
    j kmain           # Saltamos al C


.section .text

.globl get_time
get_time:
  csrr a0, time
  ret
.global get_scause
get_scause:
  csrr a0, scause
  ret

.global get_stval
get_stval:
  csrr a0, stval
  ret

.global get_sepc
get_sepc:
  csrr a0, sepc
  ret


.global sbi_call
sbi_call:
    ecall
    ret

.globl halt
halt:
  wfi
  j halt

