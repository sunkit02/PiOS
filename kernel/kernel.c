#include <stddef.h>
#include <stdint.h>

#include "mm/psr.h"
#include "peripherals/uart.h"
#include "lib/format.h"
#include "lib/string.h"
 
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
	uart_puts("Hello, this is PiOS!\n");
  uart_puts("\n");
  uart_puts("\n");

  char buf[1024];
  char *strEnd = NULL;
  
  uart_puts("CPSR: ");
  strEnd = int_bstr(get_cpsr(), buf, sizeof(buf)) + 1;
  uart_puts(buf);
  uart_puts("\n");

  uart_puts("SPSR: ");
  strEnd = int_bstr(get_spsr(), buf, sizeof(buf)) + 1;
  uart_puts(buf);
  uart_puts("\n");

  save_cpsr();

  uart_puts("SPSR AFTER SAVE: ");
  strEnd = int_bstr(get_spsr(), buf, sizeof(buf)) + 1;
  uart_puts(buf);
  uart_puts("\n");


  uart_puts("\n");
  uart_puts("\n");

  int num = 0x11223345;

  // char msg[][3] = {"12", "34", "45"};
  int msg[] = {0x1100dd, 0x2200ee, 0x3300ff};
  uart_puts("HEX: ");
  // to_xstr(&num, sizeof(num), sizeof(num), buf, 1024);
  for (int i = 0; i < 3; i++) {
    // to_xstr(&msg[i], sizeof(msg[i]), buf, sizeof(buf));
    int_bstr(msg[i], buf, sizeof(buf));
    uart_puts(buf);
    uart_puts("\n");
  }

  uart_puts("sizeof(msg)=");
  int_str(sizeof(msg), buf, sizeof(buf));
  uart_puts(buf);
  uart_puts("\n");


  uart_puts("BIN: ");
  to_bstr_end(msg, sizeof(msg), buf, sizeof(buf));
  uart_puts(buf);
  uart_puts("\n");

  int_str(sizeof(num), buf, sizeof(buf));
  uart_puts(buf);
  uart_puts("\n");

  char buffer[100];
  unsigned int n = 0;
	while (1) {
    uart_puts("Type something: ");
    uart_readline(buffer, 100);

    uart_puts("You entered: ");
    uart_puts(buffer);
    uart_puts("\n");
    uart_puts("A total of ");
    size_t len = strlen(buffer);
    int_str(len, buffer, sizeof(buffer));
    strcat(buffer, " characters.");
    uart_puts(buffer);

    uart_puts("\n");
    uart_puts("\n");
  }
}
