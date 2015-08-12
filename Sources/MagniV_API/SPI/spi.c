/** \addtogroup SPI Serial Peripheral interface
 *  @{
 */
/**	
 *  @file spi.c
 *  
 * 	@brief Contains serial peripheral interface API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */
#include "spi.h"

/**	Initializes the SPI based interface to the desired baudrate as a Master or as a Slave
 * 
 * 	@param	BusClock		Bus frequency of the device
 * 	@param	baudrate		Desired baudrate
 * 	@param	Master_Slave	MASTER/SLAVE selection (by passing the a 1 or a 0 respectively)
 * */
void spi_init(unsigned long BusClock, unsigned long baudrate, unsigned char Master_Slave){
	
}

/** Calculates the best dividers values for the desired frequency
 * 
 * 	@param BusClock Bus frequency of the device
 * 	@param baudrate	Desired baudrate
 * 	
 * 	@return Prescaler values that best match the desired baudrate, and the calculated error with these values
 * */
spi_divider spi_baud_cal(unsigned long BusClock, unsigned long baudrate){
	unsigned long baudrate_temp;
	long	error;
	unsigned int baud_div;
	unsigned char SPPR_temp, SPR_temp;
	for(SPPR_temp = 0; SPPR_temp <= SPPR_MAX; ++SPPR_temp){
		for(SPR_temp = 0; SPR_temp <= SPR_MAX; ++SPR_temp){
			baud_div = (SPPR_temp + 1) * (1 << (SPR_temp + 1));		/* Calculate baudrate divisor (1 << x equals 2^x) */
			baudrate_temp = BusClock / baud_div;					/* Calculate baudrate with current values */
			error = baudrate_temp - baudrate;
			error = error < 0 ? error * (-1) : error;				/* Error absolute value */
		}
	}
}
/** @}*/
