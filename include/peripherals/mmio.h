#ifndef __PERIPHERALS_MMIO_H
#define __PERIPHERALS_MMIO_H

#include <stdint.h>

// The MMIO area base address, depends on board type

// static uint32_t MMIO_BASE = 0x3F000000; // for raspi2 & 3
// static uint32_t MMIO_BASE = 0xFE000000; // for raspi4
static uint32_t MMIO_BASE = 0x20000000; // for raspi1, raspi zero etc.

// The MMIO area base address, depends on board type
static inline void mmio_init(int raspi) {
    switch (raspi) {
        case 2:
        case 3:  MMIO_BASE = 0x3F000000; break; // for raspi2 & 3
        case 4:  MMIO_BASE = 0xFE000000; break; // for raspi4
        default: MMIO_BASE = 0x20000000; break; // for raspi1, raspi zero etc.
    }
}

// Memory-Mapped I/O output
static inline void mmio_write(uint32_t reg, uint32_t data) {
	*(volatile uint32_t*)(MMIO_BASE + reg) = data;
}
 
// Memory-Mapped I/O input
static inline uint32_t mmio_read(uint32_t reg) {
	return *(volatile uint32_t*)(MMIO_BASE + reg);
}
 
// Loop <delay> times in a way that the compiler won't optimize away
static inline void delay(int32_t count) {
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

#endif // !__PERIPHERALS_MMIO_H
