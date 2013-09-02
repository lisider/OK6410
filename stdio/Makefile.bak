sdram.bin: start.o led.o clock.o uart.o sdram.o
	arm-linux-ld -T x.lds -o sdram.elf start.o uart.o led.o clock.o sdram.o
	arm-linux-objcopy -O binary sdram.elf sdram.bin
	arm-linux-objdump -D sdram.elf > sdram.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
uart.o : uart.c
	arm-linux-gcc -o uart.o uart.c -c 
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c
led.o : led.c
	arm-linux-gcc -o led.o led.c -c 
sdram.o : sdram.c
	arm-linux-gcc -o sdram.o sdram.c -c

clean:
	rm  -f *.o *.elf *.bin *.dis

