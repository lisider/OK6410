


void main(void)
{
	unsigned char c;

	lcd_init();
	lcd_light_on();
	displaycon_on();
	while(1)
	{
		put_s("********LCD TEST MENU********\n\r");
		put_s("[P] Draw a Point\n\r");
		put_s("[L] Draw a Line\n\r");
		put_s("[M] Draw a Mire\n\r");
		put_s("[C] Clear the Src\n\r");
		
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
				DrawLine(100, 100, 200, 200, 0xff00);
				break;
			}

			case 'c':
			case 'C':
			{
				ClearScr(0xffffff);
				break;
			}

			case 'p':
			case 'P':
			{
				PutPixel(100, 100, 0xff00);
				break;
			}

			case 'M':
			case 'm':
			{
				Mire();
				break;
			}

		}

	}
}
