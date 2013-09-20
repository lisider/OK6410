
void main(void)
{
	int i;
	unsigned char com_buf[100];
	unsigned char ch;

	put_s("Wellcome to here!\n\rok6410#");
	
	for(;;)
	{
		i = 0;
		for(;;)
		{
			ch = get_c();
			if(ch == '\r')
			{
				put_s("\n\rok6410#");
				com_buf[i] = '\0'; 
				break;
			}
			else if(ch == 8)
			{
				if(i == 0)
					continue;
				i--;
				put_c(ch);
				put_c(' ');
				put_c(ch);
			}
			else
			{
				put_c(ch);
				com_buf[i++] = ch;
			}
		}
		put_s(com_buf);
		put_s("\n\rok6410#");
	}
}
