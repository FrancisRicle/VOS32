#pragma once

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define true  1
#define false 0
#define NULL  ((void *) 0)
#define PAGE_SIZE 4096

typedef struct {
    long error;
    long value;
} sbiret;

sbiret sbi_call(long arg0, long arg1, long arg2, long arg3,
                       long arg4, long arg5, long fid, long eid);

uint32_t get_time(void);
uint32_t get_scause(void);
uint32_t get_stval(void);
uint32_t get_sepc(void);
void halt(void);
void kputc(char c);
void kputs(const char *s);
void kputd(int v);
void kputh(uint32_t v); // Imprime un número en formato 0xABC12345
void *memset(void *buf, char c, size_t n);
void init_traps(void);
void init_int(void);
void init_timer(void);
paddr_t knext_free_page(void);
paddr_t kn_free_pages(uint32_t n);
extern char __bss[], __bss_end[], __stack_top[];
struct trap_frame {
    uint32_t ra;
    uint32_t gp;
    uint32_t tp;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;
    uint32_t a5;
    uint32_t a6;
    uint32_t a7;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
    uint32_t sp;
} __attribute__((packed));
#define PANIC(fmt)\                                                 
    do {\                                                                  
      kputs("\nKERNEL PANIC on file: ");\
      kputs(__FILE__);\
      kputs(" on line: ");\
      kputd(__LINE__);\
      kputs(" panic: ");\
      kputs(fmt);\
        while (1) {}\                                                          
    } while (0)
