#include "console.h"
void putc(char c) { syscall(2, (uint32_t)c); }
void puts(const char *s) {
  while (*s) {
    putc(*s++);
  }
}
