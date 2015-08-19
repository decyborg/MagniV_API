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
/* TODO Add Polarity and Phase selection */

/**	Initializes the SPI interface to the desired baudrate as a Master
 * 
 * 	@param	BusClock		Bus frequency of the device
 * 	@param	baudrate		Desired baudrate
 * 	@param  transfer_width  Select between 8bit transfer and 16bit transfer
 * */
void spi_init_mst(unsigned long BusClock, unsigned long baudrate, unsigned char transfer_width){
	spi_divider spi_prs;
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	spi_prs = spi_baud_cal(BusClock, baudrate);				/* Calculate prescaler values */
	pSPI->spibr.bit.SPR = spi_prs.SPR;						/* Set baud rate */
	pSPI->spibr.bit.SPPR = spi_prs.SPPR;
	pSPI->spicr1.bit.mstr = 1;								/* Select Master */
	pSPI->spicr2.bit.modefen = 1;							/* Use SS */
	pSPI->spicr1.bit.ssoe = 1;
	pSPI->spicr2.bit.xfrw = transfer_width;					/* Select between 8bit and 16bit transfer */
	pSPI->spicr1.bit.spe = 1;								/* Enable SPI System */
}



/**	Initializes the SPI interface as slave
 * 
 * 	@param  transfer_width  Select between 8bit transfer and 16bit transfer
 * */
void spi_init_slv(unsigned char transfer_width){
	spi_divider spi_prs;
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	pSPI->spicr1.bit.mstr = 0;								/* Select Slave */
	pSPI->spicr2.bit.modefen = 1;							/* Use SS */
	pSPI->spicr1.bit.ssoe = 1;
	pSPI->spicr2.bit.xfrw = transfer_width;					/* Select between 8bit and 16bit transfer */
	pSPI->spicr1.bit.spe = 1;								/* Enable SPI System */
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

/** Sends data through SPI
 * 
 * @param data Data to be sent
 * */
void send_SPI(word data){
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	while(!pSPI->spisr.bit.sptef){};
	pSPI->spidr.word = data;
}

/** Receives data through SPI
 * 
 * @return Data received through SPI
 * */
word get_SPI(void){
	tSPI* pSPI = (tSPI*) SPI_ADDR;
	
	while(!pSPI->spisr.bit.spif){};									/* Wait for data */
	return pSPI->spidr.word;										/* Return received data */
}

/* TODO SPI Transfer */
/** @}*/
