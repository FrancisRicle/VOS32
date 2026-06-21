.section .text
.global sbi_call
sbi_call:
    ecall
    ret

