.section .text


.globl current_time
current_time:
1:
  csrr a1, timeh
  csrr a0, time
  csrr t0, timeh
  bne  a1, t0, 1b   # si timeh cambió mientras leíamos, repetir
  ret

.globl timer
timer:
  li t0, 32
  csrw sie, t0
  ret

.globl uret
uret:
  csrw sepc, a0
  ret
