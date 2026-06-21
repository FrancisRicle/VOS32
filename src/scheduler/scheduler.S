.section .text


.globl current_time
current_time:
  csrr a1, timeh
  csrr a0, time
  ret

.globl timer
timer:
  li t0, 32
  csrw sie, t0
  ret

.globl yield_a
yield_a:
  csrw sepc, a0
  ret
