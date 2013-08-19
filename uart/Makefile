led.bin: start.o led.o clock.o uart.o 
	arm-linux-ld -Ttext 0 -o uart.elf start.o uart.o led.o clock.o
	arm-linux-objcopy -O binary uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
uart.o : uart.c
	arm-linux-gcc -o uart.o uart.c -c 
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c
led.o : led.c
	arm-linux-gcc -o led.o led.c -c 

clean:
	rm  -f *.o uart.elf uart.bin uart.dis

