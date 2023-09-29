#include <stddef.h>
#include <stdint.h>

#include "mm/psr.h"
#include "peripherals/uart.h"
#include "lib/print.h"
 
#ifdef AARCH64
// arguments for AArch64
void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
#else
// arguments for AArch32
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
#endif
{
	// initialize UART for Raspi2
	uart_init(1);
	uart_puts("Hello, this is PiOS!\r\n");
  uart_puts("\r\n");
  uart_puts("\r\n");

  char buf[40] = { 0 };
  char *strEnd = NULL;
  
  uart_puts("CPSR: ");
  strEnd = int_bstr(get_cpsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");

  uart_puts("SPSR: ");
  strEnd = int_bstr(get_spsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");

  save_cpsr();

  uart_puts("SPSR AFTER SAVE: ");
  strEnd = int_bstr(get_spsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");


  char buffer[100];
  unsigned int n = 0;
	while (1) {
    uart_puts("Type something: ");
    uart_readline(buffer, 100);

    uart_puts("You entered: ");
    uart_puts(buffer);
    uart_puts("\r\n");
    uart_puts("A total of x");
    uart_puts(" characters.");

    uart_puts("\r\n");
    uart_puts("\r\n");
  }
}
