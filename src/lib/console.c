#include "console.h"

void putc(char c) { sbi_console_putchar(c); }
void puts(const char *s) {
  while (*s) {
    putc(*s++);
  }
}
void putd(int v) {
  const char *digits = "0123456789";
  if (v < 0) {
    putc('-');
    putd(v * (-1));
    return;
  }
  if (!v)
    putc('0');
  if (v >= 10) {
    putd(v / 10);
    putc(digits[v % 10]);
  } else {
    putc(digits[v]);
  }
}
void puth(uint32_t v) {
  const char *hex_digits = "0123456789ABCDEF";

  puts("0x");
  // Procesamos de 4 en 4 bits, empezando por los más significativos (MSB)
  for (int i = 28; i >= 0; i -= 4) {
    // Desplazamos y aislamos los 4 bits inferiores
    uint32_t nibble = (v >> i) & 0xF;
    putc(hex_digits[nibble]);
  }
}
