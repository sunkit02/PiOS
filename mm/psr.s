.global get_cpsr
get_cpsr:
  mrs   r0, cpsr
  bx    lr

.global save_cpsr
save_cpsr:
  mrs   r0, cpsr
  msr   spsr_c, #0

  mov   r1, #255 /* mask all bits except [0:7] for c */
  and   r0, r0, r1
  msr   spsr_f, r0
  bx    lr

.global get_spsr
get_spsr:
  mrs   r0, spsr
  bx    lr
