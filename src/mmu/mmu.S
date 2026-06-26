.section .text
.globl enable_mmu
enable_mmu:
    srli a0, a0, 12
    li   t0, 1
    slli t0, t0, 31
    or   a0, a0, t0
    csrw satp, a0
    sfence.vma zero, zero
    ret
