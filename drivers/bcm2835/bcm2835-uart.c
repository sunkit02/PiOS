
#include <stdint.h>
#include <stddef.h>
#include "lib/print.h"
#include "peripherals/bcm2835-gpio.h"
#include "peripherals/mmio.h"

#define DEL_CHAR 127
#define BACKSPACE_SEQUENCE "\b \b"

/* 
   The following code is from wiki.osdev.org 
   Link: https://wiki.osdev.org/Raspberry_Pi_Bare_Bones#Testing_your_operating_system_.28Real_Hardware.29
*/

// A Mailbox message with set clock rate of PL011 to 3MHz tag
volatile unsigned int  __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 2, 3000000, 0 ,0
};
 
void uart_init(int raspi) {
	mmio_init(raspi);
 
	// Disable UART0.
	mmio_write(UART0_CR, 0x00000000);
	// Setup the GPIO pin 14 && 15.
 
	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	mmio_write(GPPUD, 0x00000000);
	delay(150);
 
	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
 
	// Write 0 to GPPUDCLK0 to make it take effect.
	mmio_write(GPPUDCLK0, 0x00000000);
 
	// Clear pending interrupts.
	mmio_write(UART0_ICR, 0x7FF);
 
	// Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
	// Baud = 115200.
 
	// For Raspi3 and 4 the UART_CLOCK is system-clock dependent by default.
	// Set it to 3Mhz so that we can consistently set the baud rate
	if (raspi >= 3) {
		// UART_CLOCK = 30000000;
		size_t r = (((size_t)(&mbox) & ~0xF) | 8);
		// wait until we can talk to the VC
		while ( mmio_read(MBOX_STATUS) & 0x80000000 ) { }
		// send our message to property channel and wait for the response
		mmio_write(MBOX_WRITE, r);
		while ( (mmio_read(MBOX_STATUS) & 0x40000000) || mmio_read(MBOX_READ) != r ) { }
	}
 
	// Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
	mmio_write(UART0_IBRD, 1);
	// Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
	mmio_write(UART0_FBRD, 40);
 
	// Enable FIFO & 8 bit data transmission (1 stop bit, no parity).
	mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
 
	// Mask all interrupts.
	mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
 
	// Enable UART0, receive & transfer part of UART.
	mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}
 
void uart_putc(unsigned char c) {
	// Wait for UART to become ready to transmit.
	while ( mmio_read(UART0_FR) & (1 << 5) ) { }
	mmio_write(UART0_DR, c);
}
 
unsigned char uart_getc() {
    // Wait for UART to have received something.
    while ( mmio_read(UART0_FR) & (1 << 4) ) { }
    return mmio_read(UART0_DR);
}
 
void uart_puts(const char* str) {
	for (size_t i = 0; str[i] != '\0'; i ++)
		uart_putc((unsigned char)str[i]);
}

/* 
   The above code is from wiki.osdev.org 
   Link: https://wiki.osdev.org/Raspberry_Pi_Bare_Bones#Testing_your_operating_system_.28Real_Hardware.29
*/


// Read input from uart
unsigned int uart_readline(char *buffer, unsigned int buffer_size) {
  unsigned int i = 0;
  unsigned char c = 0;
  while (1) {
    c = uart_getc();

    // handle backspace / delete control character
    if (c == DEL_CHAR) {
      // Print sequence to overwrite previously printed character and
      // decrement i to overwrite previously written characters only 
      // when i is greater than 0 to avoid negative indexing and overwriting
      // characters printed before uart_readline() was invoked
      if (i > 0) {
        uart_puts(BACKSPACE_SEQUENCE);
        i--;
      }
      continue;
    }
    
    // Stop reading when read CR character
    // Note: Enter key code is CR in ascii (at least in QEMU)
    if (c == '\r') break;

    // Echo entered character
    uart_putc(c);

    // Only read up to buffer size (leave space for '\0')
    if (i < buffer_size - 1) {
      buffer[i++] = c;
    }
  }

  buffer[i++] = '\0';

  uart_puts("\r\n");

  return i;
}

