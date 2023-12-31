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
	printf("\n\n\nHello, this is PiOS!\n\n\n");

  char buf[1024] = { 0 };
  char *strEnd = NULL;
  
  int_bstr(get_cpsr(), buf, sizeof(buf));
  printf("CPSR: %s\n", buf);


  int_bstr(get_spsr(), buf, sizeof(buf));
  printf("SPSR: %s\n", buf);

  save_cpsr();

  int_bstr(get_spsr(), buf, sizeof(buf));
  printf("SPSR AFTER SAVE: %s\n", buf);

  printf("\n\n");

  uart_puts("\n");

  // uart_puts("MMU ENABLED: ");
  // int_str(mmu_enabled(), buf, sizeof(buf));
  // uart_puts(buf);
  // uart_puts("\n");
  //
  // uart_puts("Enabling MMU...");
  // enable_mmu();
  // uart_puts("Finished enabling MMU...");
  //
  // uart_puts("MMU ENABLED: ");
  // int_str(mmu_enabled(), buf, sizeof(buf));
  // uart_puts(buf);
  // uart_puts("\n");

  

  uintptr_t address = 0x20000000 - 100;
  volatile uint32_t *ptr = (volatile uint32_t *)address;
  to_xstr((void *)ptr, sizeof(ptr), buf, sizeof(buf));
  uart_puts("\nPRINTING MEMORY ADDRESS ");
  uart_puts(buf);
  uart_puts(":\n");


  to_xstr((void *)ptr, 100, buf, sizeof(buf));
  uart_puts(buf);
  uart_puts("\nFINISHED PRINTING MEMORY ADDRESS\n");

  // uart_puts("Invoking reset handler...\n");
  // invoke_reset_handler();

  unsigned int n = 0;
	while (1) {
    printf("Type something: ");
    uart_readline(buf, 100);

    size_t len = strlen(buf);

    printf("You entered: %s\n", buf);
    printf("A total of %d characters.\n\n", len);
  }
}
