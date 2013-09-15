#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))
#define NFCONF          (*((volatile unsigned long *)0x70200000))
#define NFCONT          (*((volatile unsigned long *)0x70200004))
#define NFCMMD          (*((volatile unsigned long *)0x70200008))
#define NFADDR          (*((volatile unsigned long *)0x7020000C))
#define NFDATA          (*((volatile unsigned char *)0x70200010))
#define NFSTAT          (*((volatile unsigned long *)0x70200028))

void nand_init(void)
{
//	MEM_SYS_CFG &= ~(1<<1);
		
#define TACLS     5
#define TWRPH0    5
#define TWRPH1    5
	NFCONF &= ~((1<<30) | (7<<12) | (7<<8) | (7<<4));
	NFCONF |= ((TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4));

	/* enable nand flash controller */
	NFCONT |= 1;
	NFCONT &= ~(1<<16);

}

void nand_addr(unsigned int addr)
{
	NFADDR = (addr & 0xff);
	NFADDR = ((addr >> 8) & 0xf);
	NFADDR = ((addr >> 12) & 0xff);
	NFADDR = ((addr >> 20) & 0xff);
	NFADDR = ((addr >> 28) & 0xff);
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

	for(i = 0; i < 6; i++)
	{		
		ch = NFDATA;
		put_c((ch >> 4) + (((ch >> 4) > 9) ? 55 : 48));
		put_c((ch & 0xf) +(((ch & 0xf) > 9) ? 55 : 48));
		put_c(' ');
	}
	NFCONT |= (1 << 1);
}

void nand_erase(unsigned int addr, unsigned int len)
{
	int i;
	len = len / (4096 * 128) + 1 ;

	for(i = 0; i < len; i++)
	{
		addr += 4096*128*i;
		NFCONT &= ~(1 << 1);
		NFCMMD = 0x60;
		NFADDR = ((addr >> 12) & 0xff);
        	NFADDR = ((addr >> 20) & 0xff);
        	NFADDR = ((addr >> 28) & 0xff);
		NFCMMD = 0xd0;
		while((NFSTAT & 0x1) == 0);
		NFCONT |= (1 << 1);
	}
	
}

void nand_write(unsigned int addr, unsigned char *str)
{
	int i;

	nand_erase(addr, 1);

	NFCONT &= ~(1 << 1);
        NFCMMD = 0x80;
	nand_addr(addr);
	
	for(i = 0; str[i] != '\0'; i++)
		NFDATA = str[i];
	NFDATA = '\0';

	NFCMMD = 0x10;
	while((NFSTAT & 0x1) == 0);
	NFCONT |= (1 << 1);
}

void nand_read(unsigned int addr)
{
	int i;

	unsigned char str[30];
	NFCONT &= ~(1 << 1);
	
	NFCMMD = 0x00;
	nand_addr(addr);
	NFCMMD = 0x30;
	while((NFSTAT & 0x1) == 0);
	
	str[0] = NFDATA;
	for(i = 1; str[i-1] != '\0'; i++)
                str[i] = NFDATA;
	NFCONT |= (1 << 1);
	
	put_s(str);
}

void nand_test()
{
	nand_write(0xff000000, "Welcome ddddddddd to here!");
	nand_read(0xff000000);
}
