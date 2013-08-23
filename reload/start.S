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

/* reload code */
	adr r0, _start
	ldr r1, =_start
	ldr r2, =bss_start
	cmp r0, r1
	beq clear_bss

reload_loop:
	ldr r3, [r0], #0x4
	str r3, [r1], #0x4
	cmp r1, r2
	bne reload_loop

clear_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r2, #0
	cmp r0, r1
	beq clear_end
clear_loop:
	str r2, [r0], #0x4
	cmp r0, r1
	bne clear_loop
clear_end:


	ldr pc, =reload_end
reload_end:




/* stack setup */
	ldr sp, =8*1024

	
	bl clock_init  	/* clock init */
//	bl led1_on
//	bl led2_on
//	bl led3_on
//	bl led4_on
//	bl uart_init
//	bl uart_loop
	bl led_loop	

halt:
	b halt	
