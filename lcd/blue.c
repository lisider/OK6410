
void Blue(void)
{

#define FRAME_BASE 0x54000000
#define HORIZONTAL 480
#define VERTICAL   272
#define BPP 24

    unsigned int x,y;
    unsigned int color;
    unsigned char red,green,blue,alpha;

    for (y = 0; y < VERTICAL; y++)
        for (x = 0; x < HORIZONTAL; x++){
            //color = ((x-xsize/2)*(x-xsize/2) + (y-ysize/2)*(y-ysize/2))/64;
            color = 256;
            red   = (color/8) % 256;
            green = (color/4) % 256;
            blue  = (color/2) % 256;
            alpha = (color*2) % 256;

            color |= ((unsigned int)alpha << 24);
            color |= ((unsigned int)red   << 16);
            color |= ((unsigned int)green << 8 );
            color |= ((unsigned int)blue       );

            //PutPixel(x,y,color);
			unsigned int *addr = (unsigned int *)FRAME_BASE + (y * HORIZONTAL + x);
			*addr =  color;
        }
}
