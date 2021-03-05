/*gpio set*/
#define GPECON  (*((volatile unsigned long *)0x7F008080))
#define GPEDAT  (*((volatile unsigned long *)0x7F008084))
#define GPFCON  (*((volatile unsigned long *)0x7F0080A0))
#define GPFDAT  (*((volatile unsigned long *)0x7F0080A4))
#define GPICON  (*((volatile unsigned long *)0x7F008100))
#define GPJCON  (*((volatile unsigned long *)0x7F008120))

/* display controller */
#define MIFPCON     (*((volatile unsigned long *)0x7410800C))
#define SPCON         (*((volatile unsigned long *)0x7F0081A0))
#define VIDCON0      (*((volatile unsigned long *)0x77100000))
#define VIDCON1      (*((volatile unsigned long *)0x77100004))
#define VIDTCON0     (*((volatile unsigned long *)0x77100010))
#define VIDTCON1     (*((volatile unsigned long *)0x77100014))
#define VIDTCON2     (*((volatile unsigned long *)0x77100018))
#define WINCON0      (*((volatile unsigned long *)0x77100020))
#define VIDOSD0A      (*((volatile unsigned long *)0x77100040))
#define VIDOSD0B      (*((volatile unsigned long *)0x77100044))
#define VIDOSD0C      (*((volatile unsigned long *)0x77100048))
#define VIDW00ADD0B0      (*((volatile unsigned long *)0x771000A0))
#define VIDW00ADD1B0      (*((volatile unsigned long *)0x771000D0))
#define VIDW00ADD2      (*((volatile unsigned long *)0x77100100))


#define  VSPW          4
#define  VBPD         23
#define  LINEVAL     599
#define  VFPD          1


#define  HSPW        128
#define  HBPD         88
#define  HOZVAL      799
#define  HFPD         40

#define LeftTopX     0
#define LeftTopY     0

#define RightBotX   799
#define RightBotY   599

#define FRAME_BUFFER   0x54000000

unsigned int fb_base_addr;
unsigned int bpp;
unsigned int xsize;
unsigned int ysize;

void lcd_init(void)
{
	GPICON = 0xaaaaaaaa;  /* set gpi0~gpi15 use for cd_vd[0~15] */
	GPJCON = 0xaaaaaaa;   /* set gpj0~gpi11 use for LCD */

	GPFCON &= ~(0x3<<28);
	GPFCON |=  (1<<28);    /* GPF14 use as lcd on/off */


	MIFPCON &= ~(1<<3);   /* Normal mode */
	SPCON    &= ~(0x3);
	SPCON    |= 0x1;            /* RGB I/F style */

	VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)  | (3<<2));     /* RGB I/F, RGB Parallel format,  */
	VIDCON0 |= ((2<<6) | (1<<4) );      /* vclk== HCLK / (CLKVAL+1) = 133/15 = 9MHz */

	VIDCON0 &= ~(0x3);

	VIDCON1 &= ~(1<<7);   /*LCD driver gets the video data at VCLK falling edge */
	VIDCON1 |= ((1<<6) | (1<<5));  /* HSYNC and VSYNC pulse polarity inverted */

	VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0xb<<2);    /* unpacked 24 BPP (non-palletized R:8-G:8-B:8 ) */

	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = ( 480 <<11) | ( 272 << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);

	VIDW00ADD0B0 = FRAME_BUFFER;
	VIDW00ADD1B0 =  (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);
	/* VBASEL = VBASEU + (LINEWIDTH+OFFSIZE) x (LINEVAL+1)
	 *        = 0 + (480*4 + 0) * 272
	 *        =
	 */
	VIDW00ADD2 =  HOZVAL + 1;

	fb_base_addr = FRAME_BUFFER;
	xsize = HOZVAL + 1;
	ysize = LINEVAL + 1;
	bpp   = 24;

}

void lcd_on(void)
{
	GPFDAT |= (1<<14);
}

static void lcd_off(void)
{
	GPFDAT &= ~(1<<14);
}
void displaycon_on(void)
{
	VIDCON0 |= 0x3;
	WINCON0 |= 1;
}

static void displaycon_off(void)
{
	VIDCON0 &= ~0x3;
	WINCON0 &= ~1;
}

static void display_red(void)
{
	volatile unsigned long *p = (volatile unsigned long *)FRAME_BUFFER;
	int x, y;
	int cnt = 0;
	unsigned long colors[] = {0xff0000, 0x00ff00, 0x0000ff, 0, 0xffffff};
	static int color_idx = 0;

	for (y = 0; y <= LINEVAL; y++)
	{
		for (x = 0; x <= HOZVAL; x++)
		{
			p[cnt++] =colors[color_idx] ;  /* red */
		}
	}

	color_idx++;
	if (color_idx == 5)
		color_idx = 0;
}
