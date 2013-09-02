
int main()
{
	char c;
	int a, b;
	
//	init_uart();
	put_s("welcome use uart!\n\r");

	printf("hello, world\n\r");

	while (1)
	{
		printf("please enter two number: \n\r");
		scanf("%d %d", &a, &b);
		printf("\n\r");
		printf("the sum is: %d\n\r", a+b);
	}
	
	return 0;
}
