.macro kernel_entry
push    {r0-r15}
.endm

.macro kernel_exit
pop     {r0-r15}
.endm

/* 
.global init_interrupt_vectors 
init_interrupt_vectors:
  adr   r0, vectors
  msr   vtor, r0
  bx    lr
*/



.section ".interrupt_vectors"
.global vectors
vectors:
  b   reset_handler
  b   undefined_handler
  b   svc_handler
  b   prefetch_abort_handler
  b   data_abort_handler
  nop         /* Reserved */
  b   irq_handler

reset_handler:
  mov   r0, #1
  bl    handle_invalid_entry
  b     err_hang

undefined_handler:
  mov   r0, #2
  bl    handle_invalid_entry
  b     err_hang

svc_handler:
  mov   r0, #3
  bl    handle_invalid_entry
  b     err_hang

prefetch_abort_handler:
  mov   r0, #4
  bl    handle_invalid_entry
  b     err_hang

data_abort_handler:
  mov   r0, #5
  bl    handle_invalid_entry
  b     err_hang

irq_handler:
  mov   r0, #6
  bl    handle_invalid_entry
  b     err_hang

.global err_hang
err_hang: b err_hang
