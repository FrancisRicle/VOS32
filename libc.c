#include "common.h"

void kputs(const char *s) {
    while (*s) {
        kputc(*s++);
    }
}
void kputd(int v) {
  const char *digits = "0123456789";
  if(v < 0) {
    kputc('-');
    kputd(v*(-1));
    return;
  }
  if(!v) kputc('0');
  if(v >= 10) {
    kputd(v / 10);
    kputc(digits[v % 10]);
  }else {
    kputc(digits[v]);
  }
}
void kputh(uint32_t v) {
    const char *hex_digits = "0123456789ABCDEF";
    
    kputs("0x");
    // Procesamos de 4 en 4 bits, empezando por los más significativos (MSB)
    for (int i = 28; i >= 0; i -= 4) {
        // Desplazamos y aislamos los 4 bits inferiores
        uint32_t nibble = (v >> i) & 0xF;
        kputc(hex_digits[nibble]);
    }
}

void klog(log_level_t level, const char* msg){
  kputs("[ ");
  kputd(get_time());
  kputs(" ]");
  // 2. Imprimir el tag según el nivel
  switch (level) {
    case LOG_OK:
      kputs(BOLD GREEN "  OK   " RESET);
      break;
    case LOG_INFO:
      kputs(BOLD BLUE "  INFO " RESET);
      break;
    case LOG_WARN:
      kputs(BOLD YELLOW "  WARN " RESET);
      break;
    case LOG_ERROR:
      kputs(BOLD RED " ERROR " RESET);
      break;
    case LOG_DEBUG:
      kputs(BOLD MAGENTA " DEBUG " RESET);
      break;
  }

  kputs(": ");
  kputs(msg);
  kputs("\n");
}

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}
