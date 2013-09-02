/*uart.c*/

#define ulcon0		*((volatile unsigned long *)0x7F005000)
#define ucon0		*((volatile unsigned long *)0x7F005004)
#define ufcon0		*((volatile unsigned long *)0x7F005008)
#define umcon0		*((volatile unsigned long *)0x7F00500C)
#define utrstat0	*((volatile unsigned long *)0x7F005010)
#define uerstat0	*((volatile unsigned long *)0x7F005014)
#define ufstat0		*((volatile unsigned long *)0x7F005018)
#define umstat0		*((volatile unsigned long *)0x7F00501C)
#define utxh0		*((volatile unsigned char *)0x7F005020)
#define urxh0		*((volatile unsigned char *)0x7F005024)
#define ubrdiv0		*((volatile unsigned long *)0x7F005028)
#define udivslot0	*((volatile unsigned long *)0x7F00502C)
#define uintp0		*((volatile unsigned long *)0x7F005030)
#define uintsp0		*((volatile unsigned long *)0x7F005034)
#define uintm0		*((volatile unsigned long *)0x7F005038)

#define gpacon		(*((volatile unsigned short *)0x7F008000))

void uart_init()
{
	gpacon &= ~0xff;
	gpacon |= 0x22;

	ulcon0 = 0x3;  //set the word length is 8-bit
	ucon0 = 0x805; //select clock PCLK
	
	ufcon0 = 0x1; //enable fifo mode

	ubrdiv0 = 0x23;
	udivslot0 = 0x1;
}

void putc(unsigned char ch)
{
	while (ufstat0 & (1<<14));
	utxh0 = ch;

}

unsigned char getc()
{
	while (!(ufstat0 & 0x3f));
	return urxh0;

}


void put_s(unsigned char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		putc(str[i++]);
	}

}

void uart_manner()
{
	put_s("Welcome use uart!\n\r");
	
}

void uart_loop()
{
	unsigned char ch;
	put_s("Welcome use uart!\n\r");

	
	for(;;)
	{
		ch = getc();
//		putc(ch);
		if(ch == '\r')
			put_s("\n\r");
		else
			putc(ch);
	}
}
