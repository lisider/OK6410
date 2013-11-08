init.bin: start.o clock.o uart.o nand.o sdram.o 
	arm-linux-ld -Ttext 0 -o init.elf start.o uart.o  clock.o nand.o sdram.o
	arm-linux-objcopy -O binary init.elf init.bin
	arm-linux-objdump -D init.elf > init.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
uart.o : uart.c
	arm-linux-gcc -o uart.o uart.c -c -nostdlib 
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c -nostdlib
nand.o : nand.c
	arm-linux-gcc -o nand.o nand.c -c -nostdlib
sdram.o : sdram.c
	arm-linux-gcc -o sdram.o sdram.c -c -nostdlib

clean:
	rm  -f *.o init.elf init.bin init.dis

