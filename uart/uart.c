/*uart.c*/

#define ulcon0		*((volatile unsigned long *)0x7F005000)
#define ucon0		*((volatile unsigned long *)0x7F005004)
#define ufcon0		*((volatile unsigned long *)0x7F005008)
#define umcon0		*((volatile unsigned long *)0x7F00500C)
#define utrstat0	*((volatile unsigned long *)0x7F005010)
#define uerstat0	*((volatile unsigned long *)0x7F005014)
#define ufstat0		*((volatile unsigned long *)0x7F005018)
#define umstat0		*((volatile unsigned long *)0x7F00501C)
#define utxh0		*((volatile unsigned char *)0x7F005020)
#define urxh0		*((volatile unsigned char *)0x7F005024)
#define ubrdiv0		*((volatile unsigned long *)0x7F005028)
#define udivslot0	*((volatile unsigned long *)0x7F00502C)
#define uintp0		*((volatile unsigned long *)0x7F005030)
#define uintsp0		*((volatile unsigned long *)0x7F005034)
#define uintm0		*((volatile unsigned long *)0x7F005038)


