#ifndef PERIPHERALS_UART_H
#define PERIPHERALS_UART_H

#include <stdint.h>
#include <stddef.h>
#include "peripherals/bcm2835-gpio.h"
#include "peripherals/mmio.h"
 
void uart_init(int raspi); 
 
void uart_putc(unsigned char c); 
 
unsigned char uart_getc(); 
 
void uart_puts(const char* str); 

unsigned int uart_readline(char *buffer, unsigned int buffer_size); 

#endif // !PERIPHERALS_UART_H
