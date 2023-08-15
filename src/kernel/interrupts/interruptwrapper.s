.globl   isr_wrapper
.align   4

.macro isr_stub number
  ISR\number:
    cli
    .if \number-8 & \number-10 & \number-11 & \number-12 & \number-13 & \number-14
      push 0
    .endif
    push $\number

    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax // kernel segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    call ExceptionHandler
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add %esp, 8
    iret
.endm

.macro irq_stub number
  IRQ\number:
    push 0
    push $\number

    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax // kernel segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    call InterruptHandler
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add %esp, 8
    iret
.endm

.macro isr_def number
  .long ISR\number
.endm

.macro irq_def number
  .long IRQ\number
.endm

.altmacro

.set i,0
.rept 32
    isr_stub %i
    .set i, i+1
.endr

.set i,0
.rept 16
    irq_stub %i
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
.globl irq_stub_table
irq_stub_table:
.set i,0
.rept 16
    irq_def %i
    .set i, i+1
.endr

