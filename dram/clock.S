.globl clock_init

clock_init:
	/* set the lock time */
	ldr r0, =0x7E00F000
	ldr r1, =0xffff

	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]


	/* set clock mode sync */
	ldr r0, =0x7E00F900
	ldr r1, [r0]
	mov r2, #0xc0
	orr r1, r1, r2
	str r1, [r0]

loop:
	ldr r1, [r0]
	ldr r2, =0xf00
	and r1, r1, r2
	cmp r1, #0xf00
	bne loop


	/* set DIV */
#define PCLK_RATIO	3
#define HCLKX2_RATIO	1
#define HCLK_RATIO	1
#define MPLL_RATIO	1
#define ARM_RATIO	0
#define CLK_DIV0_VAL ((PCLK_RATIO << 12) | (HCLKX2_RATIO << 9) | (HCLK_RATIO << 8) | (MPLL_RATIO << 4) | (ARM_RATIO << 0))
	ldr r0, =0x7E00F020
	ldr r1, [r0]
	bic r1, r1, #0x30000
	bic r1,	r1, #0xff00
	bic r1, r1, #0xff
	ldr r2, =CLK_DIV0_VAL
	orr r1, r1, r2
	str r1, [r0]

	/* set uart clock EXT_UCLK1 */
/*	ldr r0, =0x7E00F028
	ldr r1, =0x30000
	str r1, [r0]
*/

	/* set APLL 533M */

#define APLL_CON_VAL ((1 << 31) | (266 << 16) | (3 << 8) | (1 << 0))
	ldr r0, =0x7E00F00C
	ldr r1, =APLL_CON_VAL
	str r1, [r0]


	/* set MPLL 533M */

#define MPLL_CON_VAL ((1 << 31) | (266 << 16) | (3 << 8) | (1 << 0))
	ldr r0, =0x7E00F010
	ldr r1, =MPLL_CON_VAL
	str r1, [r0]
	
	/* select PLL  */
	ldr r0, =0x7E00F01C
	ldr r1, =0x2003
	str r1, [r0]
/*
mov	r1, #0x10000
wait:
	sub r1, r1, #1
	cmp r1, #0
	bne wait
*/
	/* return */
	mov pc, lr
