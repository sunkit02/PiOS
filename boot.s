# 0 "boot.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "boot.S"



.section ".text.boot"


.globl _start

        .org 0x8000






_start:

 mov sp, #0x8000


 ldr r4, =__bss_start
 ldr r9, =__bss_end
 mov r5, #0
 mov r6, #0
 mov r7, #0
 mov r8, #0
 b 2f

1:

 stmia r4!, {r5-r8}


2:
 cmp r4, r9
 blo 1b


 ldr r3, =kernel_main
 blx r3


halt:
 wfe
 b halt
