
.globl _start
_start:
	b reset
	b halt
	b halt
	b halt
	b halt
	b halt
	ldr pc, _irq
	b halt

_irq:
	.word vector_irq

vector_irq:
	sub lr, lr, #4
	stmdb sp!, {r0-r12, lr} 

	bl do_irq
	
	ldmia sp!, {r0-r12, pc}^  


reset:
/* hardware set */

	/* peri port setup */
	ldr r0, =0x70000000
	orr r0, r0, #0x13
	mcr p15, 0, r0, c15, c2, 4

	/* disable watchdog */
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]
	
	ldr r0, =0x7F008820
        ldr r1, =0x1111
        str r1, [r0]
        ldr r0, =0x7F008824
        ldr r1, =0xf
        str r1, [r0]

/* stack setup */
	ldr sp, =8*1024

	bl int_init
	msr cpsr_cxsf, #0xd2    
	ldr sp, =6*1024  
	msr cpsr_cxsf, #0x13 

halt:
	b halt	
