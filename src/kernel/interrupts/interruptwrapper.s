.globl   isr_wrapper
.align   4
 
isr_wrapper:
    pushal
    cld    //; C code following the sysV ABI requires DF to be clear on function entry
    call InterruptHandler
    popal
    iret

.macro isr_stub number
  ISR\number:
    mov $\number, %eax
	  jmp isr_wrapper
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
