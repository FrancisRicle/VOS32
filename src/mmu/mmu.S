.section .text
.globl rootpt
rootpt:
    srli a0, a0, 12 # 
    li   t0,      1 #
    slli t0, t0, 31 #
    or   a0, a0, t0 #
    sfence.vma   zero, zero # clear cache
    csrw satp,   a0 # satp <- enable sv32 | table1 >> 12
    sfence.vma   zero, zero # clear cache
    ret
