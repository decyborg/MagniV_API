/** \addtogroup SPI Serial Peripheral interface
 *  @{
 */
/**
 *  @file spi.h
 *
 * 	@brief Contains Serial peripheral interface API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */

#ifndef SPI_H_
#define SPI_H_

/* Include derivative support */
#include "derivative.h"
#include "common.h"

/* Typedefs */
/** A structure that holds the prescaler values for the baudrate configuration
 * 
 * */
typedef struct {
	unsigned char SPPR;		/**< SPI Baud Rate Preselection Bits */
	unsigned char SPR;		/**< SPI Baud Rate Selection Bits */
	unsigned long error;	/**< Calculated error with the current configuration */
}spi_divider;

/* Prototypes */
void spi_init(unsigned long BusClock, unsigned long baudrate, unsigned char Master_Slave);
spi_divider spi_baud_cal(unsigned long BusClock, unsigned long baudrate);

#endif /* SPI_H_ */
/** @}*/
