/** \addtogroup SCI Serial Communication Interface  
 *  @{
 */
/**
 *  @file sci.h
 *
 * 	@brief Contains Serial communication interface API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */
#ifndef SCI_H_
#define SCI_H_
/* Include derivative support */
#include "derivative.h"
#include "common.h"

/* Prototypes */
void sci_init(unsigned long baudrate);

#endif /* SCI_H_ */
/** @}*/
