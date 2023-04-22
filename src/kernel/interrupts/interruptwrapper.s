.macro isr_stub number
  ISR\number:
    mov $\number, %eax
	  jmp InterruptHandler
.endm

.altmacro

.macro isr_insert number
    .section .text
    isr_stub \number

    .section .data
    .globl ISR\number
.endm

.set i,0
.rept 32
    isr_insert %i
    .set i, i+1
.endr