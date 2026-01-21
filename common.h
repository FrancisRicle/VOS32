
#pragma once

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

void kputc(char c);
void kputs(const char *s);
void kprint_hex(uint32_t v); // Imprime un número en formato 0xABC12345
void *memset(void *buf, char c, size_t n);

extern char __bss[], __bss_end[], __stack_top[];
