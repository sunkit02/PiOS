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

.global mmu_enabled 
mmu_enabled:
  mrc   p15, #0, r0, c1, c0, #0
  tst   r0, #1
  bne   enabled
disabled:
  mov   r0, #0
  bx    lr
enabled:
  mov   r0, #1
  bx    lr

.global enable_mmu
enable_mmu:
  mrc   p15, #0, r0, c1, c0, #0
  orr   r0, r0, #1
  mcr   p15, #0, r0, c1, c0, #0
  bx    lr
  
.global invoke_reset_handler 
invoke_reset_handler:
  b   0x0
  bx  lr
