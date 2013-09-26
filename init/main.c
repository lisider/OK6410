
void get_para(unsigned char *command, int *offset, unsigned char *para)
{
	int i = 0;
	while(command[*offset] != ' ' && command[*offset] != '\0')
		para[i++] = command[(*offset)++];

	para[i] = '\0';

	if(cmmand[*offset] != '\0')
		(*offset)++;
}
void para_compare(unsigned char *str1, unsigned char *str2)
{
	int i = 0;
	while(str1[i] != '\0' && str1[i] == str2[i])
		i++;
	if(str1[i] == '\0' && str2[i] == '\0')
		return 0;
	else
		return 1;

}

void command_analysis(unsigned char *command)
{
	int i = 0;
	unsigned char para_1[10], para_2[10], para_3[10], para_4[10];
	unsigned int data_1, data_2, data_3;
	
	get_para(command, &i, para_1);
	
	if(para_compare(para_1, "nand")) 
		goto error;
	
	get_para(command, &i, para_2);
	if(!para_compare(para_2, "erase")) {
		ret = get_data(commamd, &i, &data_1);
		if(ret == -1)
			goto error;
		ret = get_data(conmand, &i, &data_2);
		if(ret == -1)
			goto error;

		nand_erase(data_1, data_2);
	}
		
	
	
error:
	put_s("Invalid parameter!\r\nok6410#");
	return;
}


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
//		put_s(com_buf);
//		put_s("\n\rok6410#");
		command_analysis(com_buf);
	}
}
