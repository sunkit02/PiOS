#include <stddef.h>
#include <stdint.h>

#include "mm/psr.h"
#include "peripherals/uart.h"
#include "lib/print.h"

 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
 
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

  // for (char i = 48; i < 58; ++i) {
  //   uart_puts("PiOS: ");
  //   uart_puts(&i);
  //   uart_puts("\r\n");
  //
  //   // delay(1200000000);
  // }
  //
  // uart_puts("\r\n");
  // uart_puts("\r\n");

  // for (char i = 0; i < 100; ++i) {
  //   uart_printc_num_val(i);
  // }

  char buf[40] = { 0 };
  char *strEnd = NULL;
  
  uart_puts("CPSR: ");
  strEnd = uint_bstr(get_cpsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");

  uart_puts("SPSR: ");
  strEnd = uint_bstr(get_spsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");

  save_cpsr();

  uart_puts("SPSR AFTER SAVE: ");
  strEnd = uint_bstr(get_spsr(), buf) + 1;
  uart_puts(buf);
  uart_puts("\r\n");



  char buffer[100];
 
	while (1) {
    uart_puts("Type something: ");
    uart_readline(buffer, 100);

    uart_puts("You entered: ");
    uart_puts(buffer);
    uart_puts("\r\n");
    uart_puts("\r\n");
  }
}
