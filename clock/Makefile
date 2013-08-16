led.bin: start.o led.o clock.o
	arm-linux-ld -Ttext 0 -o clock.elf start.o clock.o led.o
	arm-linux-objcopy -O binary clock.elf clock.bin
	arm-linux-objdump -D clock.elf > clock.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
clock.o : clock.S
	arm-linux-gcc -o clock.o clock.S -c
led.o : led.c
	arm-linux-gcc -o led.o led.c -c

clean:
	rm  -f *.o clock.elf clock.bin clock.dis

