#include "common.h"

void kputs(const char *s) {
    while (*s) {
        kputc(*s++);
    }
}
void kprint_hex(uint32_t v) {
    const char *hex_digits = "0123456789ABCDEF";
    
    kputs("0x");
    // Procesamos de 4 en 4 bits, empezando por los más significativos (MSB)
    for (int i = 28; i >= 0; i -= 4) {
        // Desplazamos y aislamos los 4 bits inferiores
        uint32_t nibble = (v >> i) & 0xF;
        kputc(hex_digits[nibble]);
    }
}

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}
