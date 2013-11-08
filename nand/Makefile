nand.bin: start.o led.o clock.o uart.o nand.o 
	arm-linux-ld -Ttext 0 -o nand.elf start.o uart.o led.o clock.o nand.o 
	arm-linux-objcopy -O binary nand.elf nand.bin
	arm-linux-objdump -D nand.elf > nand.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c -nostdlib
uart.o : uart.c 
	arm-linux-gcc -o uart.o uart.c -c  -nostdlib
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c -nostdlib
led.o : led.c
	arm-linux-gcc -o led.o led.c -c -nostdlib
nand.o : nand.c
	arm-linux-gcc -o nand.o nand.c -c -nostdlib

clean:
	rm  -f *.o nand.elf nand.bin nand.dis

