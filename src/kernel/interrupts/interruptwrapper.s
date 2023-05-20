.globl   isr_wrapper
.align   4

.macro isr_stub number
  ISR\number:
    mov $\number, %eax
	  pushal
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    push %eax
    call InterruptHandler
    pop %eax
    popal
    iret
.endm

.macro isr_def number
  .long ISR\number
.endm

.altmacro

.set i,0
.rept 32
    isr_stub %i
    .set i, i+1
.endr

.section .data
.globl isr_stub_table
isr_stub_table:
.set i,0
.rept 32
    isr_def %i
    .set i, i+1
.endr
