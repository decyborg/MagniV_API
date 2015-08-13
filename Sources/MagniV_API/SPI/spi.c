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
	unsigned long baudrate_temp, min_error;
	long	error;
	unsigned int baud_div;
	unsigned char SPPR_temp, SPR_temp;
	spi_divider spi_pr;
	min_error = 0;													/* Initialize temporary error variable */
	
	for(SPPR_temp = 0; SPPR_temp <= SPPR_MAX; ++SPPR_temp){
		for(SPR_temp = 0; SPR_temp <= SPR_MAX; ++SPR_temp){
			baud_div = (SPPR_temp + 1) * (1 << (SPR_temp + 1));		/* Calculate baudrate divisor (1 << x equals 2^x) */
			baudrate_temp = BusClock / baud_div;					/* Calculate baudrate with current values */
			error = baudrate_temp - baudrate;
			error = error < 0 ? error * (-1) : error;				/* Error absolute value */
			if(error == 0){											/* Perfect match return values */
				spi_pr.SPPR = SPPR_temp;
				spi_pr.SPR = SPR_temp;
				spi_pr.error = error;
				return spi_pr;
			} else{
				if(min_error == 0){									/* First time it enters the loop */
					spi_pr.SPPR = SPPR_temp;						/* Store values */
					spi_pr.SPR = SPR_temp;
					spi_pr.error = error;
					min_error = error;
				} else if(error < min_error){						/* Better values have been found */
					spi_pr.SPPR = SPPR_temp;
					spi_pr.SPR = SPR_temp;
					spi_pr.error = error;
					min_error = error;								/* Update minimum error */
				}
			}
		}
	}
	
	return spi_pr;													/* Return found values that better match the baudrate */
}
/** @}*/
