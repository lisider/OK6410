


void main(void)
{
	unsigned char c;
	static int lcdon = 0;
	static int dispon = 0;

	lcd_init();

	while(1)
	{
		put_s("********LCD TEST MENU********\n\r");
		put_s("[L] enable/disable LCD\n\r");
		put_s("[C] enable/disable s3c6410 display controller\n\r");
		put_s("[D] display color\n\r");
		put_s("[Q] quit\n\r");
		
		do {
			c = get_c();
			if (c == '\n' || c == '\r')
			{
				put_s("\n\r");
			}
			else
			{
				put_c(c);
			}
		} while (c == '\n' || c == '\r');

		switch (c) {
			case 'l':
			case 'L':
			{
				if (lcdon)
				{
					lcd_off();
					put_s("LCD off\n\r");
				}
				else
				{
					lcd_on();
					put_s("LCD on\n\r");
				}
				lcdon = !lcdon;
				break;
			}

			case 'c':
			case 'C':
			{
				if (dispon)
				{
					displaycon_off();
					put_s("Display controller off\n\r");
				}
				else
				{
					displaycon_on();
					put_s("Display controller on\n\r");
				}
				dispon = !dispon;
				break;
			}

			case 'd':
			case 'D':
			{
				display_red();
				break;
			}

			case 'q':
			case 'Q':
			{
				return ;
				break;
			}

		}

	}
}
