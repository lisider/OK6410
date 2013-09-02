nand.bin: start.o led.o clock.o uart.o nand.o 
	arm-linux-ld -Ttext 0 -o nand.elf start.o uart.o led.o clock.o nand.o
	arm-linux-objcopy -O binary nand.elf nand.bin
	arm-linux-objdump -D nand.elf > nand.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
uart.o : uart.c
	arm-linux-gcc -o uart.o uart.c -c 
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c
led.o : led.c
	arm-linux-gcc -o led.o led.c -c 
nand.o : nand.c
	arm-linux-gcc -o nand.o nand.c -c

clean:
	rm  -f *.o nand.elf nand.bin nand.dis

