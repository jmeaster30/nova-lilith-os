.globl ISR0
.globl ISR1
.globl ISR2
.globl ISR3
.globl ISR4
.globl ISR5
.globl ISR6
.globl ISR7
.globl ISR8
.globl ISR9
.globl ISR10
.globl ISR11
.globl ISR12
.globl ISR13
.globl ISR14
.globl ISR15
.globl ISR16
.globl ISR17
.globl ISR18
.globl ISR19
.globl ISR20
.globl ISR21
.globl ISR22
.globl ISR23
.globl ISR24
.globl ISR25
.globl ISR26
.globl ISR27
.globl ISR28
.globl ISR29
.globl ISR30
.globl ISR31

ISR0:
	mov $0, %eax
	jmp InterruptHandler
	
ISR1:
	xchgw %bx, %bx
	mov $1, %eax
	jmp InterruptHandler
	
ISR2:
	xchgw %bx, %bx
	mov $2, %eax
	jmp InterruptHandler
	
ISR3:
	mov $3, %eax
	jmp InterruptHandler
	
ISR4:
	mov $4, %eax
	jmp InterruptHandler
	
ISR5:
	mov $5, %eax
	jmp InterruptHandler
	
ISR6:
	mov $6, %eax
	jmp InterruptHandler
	
ISR7:
	mov $7, %eax
	jmp InterruptHandler
	
ISR8:
	mov $8, %eax
	jmp InterruptHandler
	
ISR9:
	mov $9, %eax
	jmp InterruptHandler
	
ISR10:
	mov $10, %eax
	jmp InterruptHandler
	
ISR11:
	mov $11, %eax
	jmp InterruptHandler
	
ISR12:
	mov $12, %eax
	jmp InterruptHandler
	
ISR13:
	mov $13, %eax
	jmp InterruptHandler
	
ISR14:
	mov $14, %eax
	jmp InterruptHandler
	
ISR15:
	mov $15, %eax
	jmp InterruptHandler
	
ISR16:
	mov $16, %eax
	jmp InterruptHandler
	
ISR17:
	mov $17, %eax
	jmp InterruptHandler
	
ISR18:
	mov $18, %eax
	jmp InterruptHandler

ISR19:
	mov $19, %eax
	jmp InterruptHandler

ISR20:
	mov $20, %eax
	jmp InterruptHandler

ISR21:
	mov $21, %eax
	jmp InterruptHandler

ISR22:
	mov $22, %eax
	jmp InterruptHandler

ISR23:
	mov $23, %eax
	jmp InterruptHandler

ISR24:
	mov $24, %eax
	jmp InterruptHandler

ISR25:
	mov $25, %eax
	jmp InterruptHandler

ISR26:
	mov $26, %eax
	jmp InterruptHandler

ISR27:
	mov $27, %eax
	jmp InterruptHandler

ISR28:
	mov $28, %eax
	jmp InterruptHandler

ISR29:
	mov $29, %eax
	jmp InterruptHandler

ISR30:
	mov $30, %eax
	jmp InterruptHandler

ISR31:
	mov $31, %eax
	jmp InterruptHandler
