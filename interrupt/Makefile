led.bin: start.o  int.o
	arm-linux-ld -Ttext 0 -o led.elf start.o  int.o
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c -nostdlib
int.o : int.c
	arm-linux-gcc -o int.o int.c -c -nostdlib
clean:
	rm  -f *.o led.elf led.bin led.dis

