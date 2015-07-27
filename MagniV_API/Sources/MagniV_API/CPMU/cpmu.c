/**	
 *  @file cpmu.c
 *  
 * 	@brief Contains Clock and power management unit API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */
/*
 * History:
 * 
 * 		Rev 1.0 Initial Release
 * 		
 * */

/* Include derivative support */
#include "derivative.h"
#include "cpmu.h"

#ifdef _MC9S12ZVL32_H /* S12ZVL32 specific functions */
/** Initializes the Bus clock at the desired speed.
 * 
 * 	@param BusClock Desired Bus Clock Frequency in hertz
 * */
void clock_init(unsigned long BusClock){
	clock_dividers prescalers;
	prescalers = PLL(BusClock*2);
}
#endif /* END of S12ZVL32 specific functions */

/** PLL
 * 
 * */
clock_dividers PLL(unsigned long FPLL ){
	unsigned long freq = (FPLL / 2000000) - 1;
	if(freq < 0)
		freq = 1;
	
}
