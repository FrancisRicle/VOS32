.section .text
.globl panic

panic:
    mv t0, a0
    li    a0, '\n'
    call  putc
    mv a0, t0
    call  puts

    li    a0, '\n'
    call  putc

    la    a0, str_sepc
    call  puts
    csrr  a0, sepc
    call  puth
    li    a0, '\n'
    call  putc

    la    a0, str_scause
    call  puts
    csrr  a0, scause
    call  puth
    li    a0, '\n'
    call  putc

    la    a0, str_stval
    call  puts
    csrr  a0, stval
    call  puth
    li    a0, '\n'
    call  putc

    csrr  t0, scause
    srli  t1, t0, 31
    bnez  t1, .is_interrupt

.is_exception:
    la    a0, str_exc_id
    call  puts
    csrr  a0, scause
    andi  a0, a0, 0xF
    call  putd
    li    a0, '\n'
    call  putc
    j     .halt

.is_interrupt:
    la    a0, str_int_id
    call  puts
    csrr  a0, scause
    andi  a0, a0, 0xF
    call  putd
    li    a0, '\n'
    call  putc

.halt:
    j     .halt

.section .rodata
str_sepc:
    .string "instruction address: "
str_scause:
    .string "cause: "
str_stval:
    .string "with: "
str_exc_id:
    .string "exception id: "
str_int_id:
    .string "interrupt id: "
