#define gpmcon *((volatile unsigned long *)0x7F008820)
#define gpmdat *((volatile unsigned long *)0x7F008824)


void delay()
{
	volatile int i = 0x10000;
	while (i--);
}

void delay_long()
{
	volatile int i = 0x100000;
	while(i--);

}

void led_init(void)
{
	gpmcon = 0x1111;
	gpmdat = 0xf;

}

int led_loop()
{
	int i = 0;
/*	
	volatile unsigned long *gpmcon = (volatile unsigned long *)0x7F008820;
	volatile unsigned long *gpmdat = (volatile unsigned long *)0x7F008824;
	
	*gpmcon = 0x1111;
*/
	led_init();
	
	while (1)
	{
		gpmdat = i;
		i++;
		if (i == 16)
			i = 0;
		delay();
	}
	
	return 0;
}

int led1_on()
{
	led_init();
	gpmdat = 0xe;
	delay();

	return 0;
}

int led2_on()
{
	led_init();
	gpmdat = 0xd;
	delay();

	return 0;
}
int led3_on()
{
	led_init();
	gpmdat = 0xb;
	delay();

	return 0;
}
int led4_on()
{
	led_init();
	gpmdat = 0x7;
	delay();

	return 0;
}
