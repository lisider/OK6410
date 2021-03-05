////////////////////////////////////////////////////////////////////////////////
////// 						S3C6410侧 寄存器
////////////////////////////////////////////////////////////////////////////////


/* gpio controller */
#define GPECON  (*((volatile unsigned long *)0x7F008080))
#define GPEDAT  (*((volatile unsigned long *)0x7F008084))
#define GPFCON  (*((volatile unsigned long *)0x7F0080A0))
#define GPFDAT  (*((volatile unsigned long *)0x7F0080A4))
#define GPICON  (*((volatile unsigned long *)0x7F008100))
#define GPJCON  (*((volatile unsigned long *)0x7F008120))

// GPACONSLP 0x7F00800C R/W Port A Sleep mode Configuration Register 0x0
#define MIFPCON     	(*((volatile unsigned long *)0x7410800C))
// SPCON 0x7F0081A0 R/W Special Port Configuration Register 0xBFC11500
#define SPCON         	(*((volatile unsigned long *)0x7F0081A0))

/* display controller */
#define VIDCON0      	(*((volatile unsigned long *)0x77100000))
#define VIDCON1      	(*((volatile unsigned long *)0x77100004))
#define VIDTCON0     	(*((volatile unsigned long *)0x77100010))
#define VIDTCON1     	(*((volatile unsigned long *)0x77100014))
#define VIDTCON2     	(*((volatile unsigned long *)0x77100018))
#define WINCON0      	(*((volatile unsigned long *)0x77100020))
#define VIDOSD0A      	(*((volatile unsigned long *)0x77100040))
#define VIDOSD0B      	(*((volatile unsigned long *)0x77100044))
#define VIDOSD0C      	(*((volatile unsigned long *)0x77100048))
#define VIDW00ADD0B0   	(*((volatile unsigned long *)0x771000A0))
#define VIDW00ADD1B0  	(*((volatile unsigned long *)0x771000D0))
#define VIDW00ADD2      (*((volatile unsigned long *)0x77100100))


////////////////////////////////////////////////////////////////////////////////
////// 						LCD 侧 :FIT-LCD4.3
////////////////////////////////////////////////////////////////////////////////

#define RGB 1

#define Horizontal_resolution 	480 // 水平
#define Vertical_resolution 	272 // 竖直
#define BitsPerPixel 			24
#define DATA_INTERFACE_MODE 	RGB


#define HOZVAL 		(Horizontal_resolution-1)
#define LINEVAL 	(Vertical_resolution-1)

#define RightBotX   HOZVAL
#define RightBotY   LINEVAL
//#define LeftTopX     290
//#define LeftTopY     260
#define LeftTopX     0
#define LeftTopY     0


////////////////////////////////////////////////////////////////////////////////




#define  VSPW          9
#define  VBPD         1
#define  VFPD          1

#define  HSPW        40
#define  HBPD         1
#define  HFPD         1

#define FRAME_BUFFER   0x54000000

unsigned int fb_base_addr;
unsigned int bpp;
unsigned int xsize;
unsigned int ysize;

void lcd_init(void)
{

	// GPIO CONFIG
	GPICON = 0xaaaaaaaa;  /* set gpi0~gpi15 use for cd_vd[0~15] */
	GPJCON = 0xaaaaaaa;   /* set gpj0~gpi11 use for LCD */

	GPFCON &= ~(0x3<<28);
	GPFCON |=  (1<<28);    /* GPF14 use as lcd on/off */


	// sleep mode 的时候 输出 1
	MIFPCON &= ~(1<<3);   /* Normal mode */


	if (DATA_INTERFACE_MODE == RGB){
		// 最低两位 为 0b01
		SPCON    &= ~(0x3);
		SPCON    |= 0x1;            /* RGB I/F style */
	}

	// ~(3<<26)   // RGB interface
	// ~(3<<17)   // RGB Parallel format (RGB)
	// ~(3<<2) 	  // Video Clock source : HCLK

	VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)  | (3<<2));     /* RGB I/F, RGB Parallel format,  */
	// (2<<6) 	// VCLK = Video Clock source/3 , CLKVAL = 2
	// (1<<4) 	// clock source  Divided by CLKVAL_F
	/* vclk== HCLK / (CLKVAL+1) = 133/15 = 9MHz */ // ???
	// vclk== HCLK / (CLKVAL+1) = 133/3 = 44.3MHz
	VIDCON0 |= ((2<<6) | (1<<4) ); 

	// Disable the video output and the Display control signal
	VIDCON0 &= ~(0x3);


	/*LCD driver gets the video data at VCLK falling edge */
	VIDCON1 &= ~(1<<7);
	/* HSYNC and VSYNC pulse polarity inverted */
	VIDCON1 |= ((1<<6) | (1<<5));

	// Vertical back porch is the number of inactive lines at the start of a frame, after vertical synchronization period.
	// Vertical front porch is the number of inactive lines at the end of a frame, before vertical synchronization period.
	// Vertical sync pulse width determines the VSYNC pulse's high level width by counting the number of inactive lines.
	VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);


	// These bits determine the vertical size of display
	// These bits determine the horizontal size of display
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	// Select the BPP (Bits Per Pixel) mode Window image.
	if (BitsPerPixel == 24){
		WINCON0 &= ~(0xf << 2);
		WINCON0 |= (0xb<<2);    /* unpacked 24 BPP (non-palletized R:8-G:8-B:8 ) */
	}

	// Horizontal screen coordinate for left top pixel of OSD image
	/* Vertical screen coordinate for left top pixel of OSD image
	   (for interlace TV output, this value MUST be set to half of the
	   original screen y coordinate. And the original screen y coordinate
	   MUST be even value.) */
	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	// Horizontal screen coordinate for right bottom pixel of OSD image
	// Vertical screen coordinate for right bottom pixel of OSD image
	VIDOSD0B = ( RightBotX <<11) | ( RightBotY << 0);
	// Window Size
	// Height * Width (Number of Word)
	VIDOSD0C = (Vertical_resolution) * (Horizontal_resolution);

	// Window 0’s buffer start address register, buffer 0
	VIDW00ADD0B0 = FRAME_BUFFER;
	// Window 0’s buffer end address register, buffer 0
	//VIDW00ADD1B0 =  ((Horizontal_resolution*4 + FRAME_BUFFER) * Vertical_resolution) & (0xffffff);
	VIDW00ADD1B0 =  (FRAME_BUFFER+(Horizontal_resolution*4*Vertical_resolution)) & (0xffffff);
	/* VBASEL = VBASEU + (LINEWIDTH+OFFSIZE) x (LINEVAL+1)
	 *        = 0 + (480*4 + 0) * 272
	 *        =
	 */
	// Window 0’s buffer size register
	// 不用设置
	//VIDW00ADD2 =  Horizontal_resolution;

	fb_base_addr = FRAME_BUFFER;
	xsize = Horizontal_resolution;
	ysize = Vertical_resolution;
	bpp   = BitsPerPixel;

}

void lcd_light_on(void)
{
	GPFDAT |= (1<<14);
}

static void lcd_off(void)
{
	GPFDAT &= ~(1<<14);
}
void displaycon_on(void)
{
	// Enable the video output and the Display control signal
	VIDCON0 |= 0x3;
	// Enable the video output and the VIDEO control signal
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
