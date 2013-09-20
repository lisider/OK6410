#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))
#define NFCONF          (*((volatile unsigned long *)0x70200000))
#define NFCONT          (*((volatile unsigned long *)0x70200004))
#define NFCMMD          (*((volatile unsigned long *)0x70200008))
#define NFADDR          (*((volatile unsigned long *)0x7020000C))
#define NFDATA          (*((volatile unsigned char *)0x70200010))
#define NFSTAT          (*((volatile unsigned long *)0x70200028))

typedef unsigned int u32;

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

void nand_erase(u32 addr, u32 len)
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

void nand_write_addr(u32 page, u32 page_offset)
{
	NFADDR = page_offset & 0xff;
	NFADDR = (page_offset >> 8) & 0xf;
	NFADDR = page & 0xff;
	NFADDR = (page >> 8) & 0xff;
	NFADDR = (page >> 16) & 0xff;
}

void nand_page_write(u32 page, u32 page_offset, unsigned char *data, u32 len)
{
	int i;

	NFCONT &= ~(1 << 1);
        NFCMMD = 0x80;
	nand_write_addr(page, page_offset);
	for(i = 0; i < len; i++)
		NFDATA = data[i];
	
	NFCMMD = 0x10;
        while((NFSTAT & 0x1) == 0);
        NFCONT |= (1 << 1);
}

void copy_from_dram_to_nand(u32 dram_addr, u32 nand_addr, u32 len)
{
	u32 page, page_offset;
	u32 count = 0, write_size = 0;
	
	page = nand_addr / 4096;
	page_offset = nand_addr & ((page <= 4) ? 0x7ff : 0xfff);

	while(count < len)
	{
		if(page <= 4){
			write_size = (len - count) > 2048 ? 2048 : (len - count);
			write_size = ((write_size + page_offset) > 2048) ? (2048 - page_offset)  : write_size;
		}
		else {
			write_size = (len - count) > 4096 ? 4096 : (len - count);
			write_size = ((write_size + page_offset) > 4096) ? (4096 - page_offset) : write_size;
		}

		

		nand_page_write(page, page_offset, (unsigned char *)dram_addr, write_size);
		page_offset = 0;
		dram_addr += write_size;
		count += write_size;
		page++;
	}

}

