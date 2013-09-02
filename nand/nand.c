#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))
#define NFCONF          (*((volatile unsigned long *)0x70200000))
#define NFCONT          (*((volatile unsigned long *)0x70200004))
#define NFCMMD          (*((volatile unsigned long *)0x70200008))
#define NFADDR          (*((volatile unsigned long *)0x7020000C))
#define NFDATA          (*((volatile unsigned char *)0x70200010))
#define NFSTAT          (*((volatile unsigned long *)0x70200028))

void nand_init(void)
{
	MEM_SYS_CFG &= ~(1<<1);
	
#define TACLS     5
#define TWRPH0    5
#define TWRPH1    5
	NFCONF &= ~((1<<30) | (7<<12) | (7<<8) | (7<<4));
	NFCONF |= ((TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4));

	/* enable nand flash controller */
	NFCONT |= 1;

}

void print_id(void)
{
	unsigned char ch;
	int i;

	NFCONT &= ~(1 << 1);
	NFCMMD = 0xff;
	while((NFSTAT & 0x1) == 0);
	NFCMMD = 0x90;
	NFADDR = 0x00;
	while((NFSTAT & 0x1) == 0);
/*
	ch[0] = NFDATA;
	ch[1] = NFDATA;
	ch[2] = NFDATA;
	ch[3] = NFDATA;
	ch[4] = NFDATA;
	ch[5] = NFDATA;
*/	

	
	for(i = 0; i < 6; i++)
	{		
		ch = NFDATA;
		put_c((ch >> 4) + (((ch >> 4) > 9) ? 55 : 48));
		put_c((ch & 0xf) +(((ch & 0xf) > 9) ? 55 : 48));
		put_c(' ');
	}
	NFCONT |= (1 << 1);
}


