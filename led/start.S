
.globl _start
_start:

/* hardware set */

	/* peri port setup */
	ldr r0, =0x70000000
	orr r0, r0, #0x13
	mcr p15, 0, r0, c15, c2, 4

	/* disable watchdog */
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]


/* stack setup */
	ldr sp, =8*1024

	bl led1_on
	bl led2_on
	bl led3_on
	bl led4_on
	bl led_loop

halt:
	b halt	
