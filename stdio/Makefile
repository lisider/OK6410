
CC	= arm-linux-gcc
LD	= arm-linux-ld
AR	= arm-linux-ar
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump

INCLUDEDIR	:= $(shell pwd)/include
CFLAGS		:= -Wall -Os -fno-builtin-printf
CPPFLAGS	:= -nostdinc -I$(INCLUDEDIR)

export CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

objs := start.o main.o uart.o clock.o sdram.o led.o lib/libc.a

stdio.bin: $(objs)
	${LD} -Tx.lds -o stdio.elf $^
	${OBJCOPY} -O binary -S stdio.elf $@
	${OBJDUMP} -D stdio.elf > stdio.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC}  -c -o $@ $<

%.o:%.S
	${CC}  -c -o $@ $<

clean:
	make  clean -C lib
	rm -f stdio.bin stdio.elf stdio.dis *.o
	
