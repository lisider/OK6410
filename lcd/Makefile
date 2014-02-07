lcd.bin: start.o clock.o uart.o lcd.o sdram.o main.o framebuffer.o
	arm-linux-ld -Ttext 0 -o lcd.elf  start.o uart.o  clock.o lcd.o sdram.o main.o framebuffer.o
	arm-linux-objcopy -O binary lcd.elf lcd.bin
	arm-linux-objdump -D lcd.elf > lcd.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
uart.o : uart.c
	arm-linux-gcc -o uart.o uart.c -c -nostdlib 
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c -nostdlib
lcd.o : lcd.c
	arm-linux-gcc -o lcd.o lcd.c -c -nostdlib
sdram.o : sdram.c
	arm-linux-gcc -o sdram.o sdram.c -c -nostdlib
main.o : main.c
	arm-linux-gcc -o main.o main.c -c -nostdlib
framebuffer.o : framebuffer.c
	arm-linux-gcc -o framebuffer.o framebuffer.c -c -nostdlib

clean:
	rm  -f *.o lcd.elf lcd.bin lcd.dis

