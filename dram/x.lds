SECTIONS
{
	. = 0x1000;

	.text :
	{
		start.o
		* (.text)
	}
	.= ALIGN(4);

	.rodata :
	{
		* (.rodata)
	}    
	. = ALIGN(4);

	.data :
	{
		* (.data)
	}
	. = ALIGN(4);	

	 bss_start = . ;  
    
	.bss :
	{
		* (.bss)     
		* (.common)
	}
	bss_end = . ; 
}	

