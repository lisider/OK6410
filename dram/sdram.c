#include "common.h"
#include "ok6410.h"

#define HCLK	133000000
#define nstoclk(ns)	(ns/( 1000000000/HCLK)+1)

void sdram_init(void)
{
	/* set dramc to config mode*/
	set_val(P1MEMCCMD, 0x4); 

	// set refresh period	
	set_val( P1REFRESH, nstoclk(7800) );
	// set timing para		
	set_val( P1CASLAT, ( 3 << 1 ) ); 
	


}
