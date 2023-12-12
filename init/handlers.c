#include "handlers.h"
#include "peripherals/uart.h"
#include "lib/string.h"

void handle_invalid_entry(int entryNum) {
  char *error_message = NULL;

  switch (entryNum) {
    case 1: {
      error_message = "Handling RESET";
      break;
    }
    case 2:{
      error_message = "Handling UNDEFINED";
      break;
    }
    case 3:{
      error_message = "Handling SVC";
      break;
    }
    case 4:{
      error_message = "Handling PREFETCH_ABORT";
      break;
    }
    case 5:{
      error_message = "Handling DATA_ABORT";
      break;
    }
    case 6:{
      error_message = "Handling IRQ";
      break;
    }
  }
}
