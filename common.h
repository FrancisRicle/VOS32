#pragma once

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define true  1
#define false 0
#define NULL  ((void *) 0)

typedef enum {
    LOG_INFO,
    LOG_OK,
    LOG_WARN,
    LOG_ERROR,
    LOG_DEBUG
} log_level_t;

void klog(log_level_t level, const char *msg);

uint32_t get_time(void);
void kputc(char c);
void kputs(const char *s);
void kputd(int v);
void kputh(uint32_t v); // Imprime un número en formato 0xABC12345
void *memset(void *buf, char c, size_t n);

extern char __bss[], __bss_end[], __stack_top[];
