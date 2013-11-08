#define VIC0IRQSTARUS	*((volatile unsigned int *)0x71200000)
#define VIC1IRQSTARUS	*((volatile unsigned int *)0x71300000)
#define VIC0INTENABLE	*((volatile unsigned int *)0x71200010)
#define VIC1INTENABLE	*((volatile unsigned int *)0x71300010)
#define VIC0INTENCLEAR	*((volatile unsigned int *)0x71200014)
#define VIC1INTENCLEAR	*((volatile unsigned int *)0x71300014)

#define VIC0VECTADDR0	*((volatile unsigned long *)0x71200100)
#define VIC0VECTADDR1	*((volatile unsigned long *)0x71200104)
#define VIC0ADDRESS	*((volatile unsigned long *)0x71200f00)

#define GPNCON     	*((volatile unsigned long *)0x7F008830)
#define GPNDAT     	*((volatile unsigned long *)0x7F008834)
#define EINT0CON0  	*((volatile unsigned long *)0x7F008900)
#define EINT0MASK  	*((volatile unsigned long *)0x7F008920)
#define EINT0PEND  	*((volatile unsigned long *)0x7F008924)
#define PRIORITY    	*((volatile unsigned long *)0x7F008280)
#define SERVICE     	*((volatile unsigned long *)0x7F008284)
#define SERVICEPEND 	*((volatile unsigned long *)0x7F008288)
#define gpmcon 		*((volatile unsigned long *)0x7F008820)
#define gpmdat 		*((volatile unsigned long *)0x7F008824)

void eint0_3(void)
{
	if(EINT0PEND & 0x1){
		if(GPNDAT & 0x1)
			gpmdat = 0xf;
		else
			gpmdat = 0xe;
	}else if(EINT0PEND & 0x2){
		if(GPNDAT & 0x2)
                        gpmdat = 0xf;
                else
                        gpmdat = 0xd;
        }else if(EINT0PEND & 0x4){
		if(GPNDAT & 0x4)
                        gpmdat = 0xf;
                else
                        gpmdat = 0xc;
	}else{
		if(GPNDAT & 0x8)
                        gpmdat = 0xf;
                else
                        gpmdat = 0xb;
	}
}

void eint4_11(void)
{
	if(EINT0PEND & 0x10){
                if(GPNDAT & 0x10)
                        gpmdat = 0xf;
                else
                        gpmdat = 0xa;
        }else if(EINT0PEND & 0x20){
                if(GPNDAT & 0x20)
                        gpmdat = 0xf;
                else
                        gpmdat = 0x9;
	}
}


void do_irq(void)
{
	int i = 0;

	void (*the_isr)(void);
//	the_isr = VIC0ADDRESS;
		
//	VIC0INTENCLEAR |= 0x3;
//	the_isr();
	if(VIC0IRQSTARUS & 0x1)
		eint0_3();
	if(VIC0IRQSTARUS & 0x2)
		eint4_11();	
	EINT0PEND   = 0x3f;
//	VIC0INTENABLE |= (0x3); 
//	VIC0ADDRESS = 0;
}


void int_init(void)
{
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;
	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;
	EINT0MASK &= ~(0x3f);
	VIC0INTENABLE |= (0x3);
	VIC0VECTADDR0 = eint0_3;
	VIC0VECTADDR1 = eint4_11;
}
