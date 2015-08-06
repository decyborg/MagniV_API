/** \addtogroup SCI Serial Communication interface
 *  @{
 */
/**	
 *  @file sci.c
 *  
 * 	@brief Contains serial communication interface API routines for MagniV devices.
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
#include "sci.h"


/**	Initializes the SCI interface to the desired baudrate
 * 
 * 	This function initializes the desired SCI channel to the desired baudrate. It must be called after the
 * 	bus clock has been set, since it uses the bus frequency to set the baudrate. The number of SCI channels is 
 * 	derivative dependent. Simply type SCIx, where x is the channel you would like to use e.g. SCI0 for channel 0.
 * 	
 *	@param baudrate			Desired baudrate
 *	@param bus_frequency	Bus frequency at which the device is working
 *	@param sci_channel		SCI channel to be used
 *	 
 * */
void sci_init(unsigned long baudrate, unsigned long bus_frequency, unsigned int sci_channel){
	tSCI* pSCI = (tSCI*) sci_channel;
	word SBR;
	
	SBR = bus_frequency / baudrate;
	pSCI->scibdh.byte = (unsigned char) (SBR >> 8);
	pSCI->scibdl.byte = (unsigned char) SBR & 0xFF;
	pSCI->scicr2.bit.te = 1;			/* Enable transmitter */
	pSCI->scicr2.bit.re = 1;			/* Enable receiver */
	if(sci_channel == SCI0){
		MODRR0_S0L0RR = 0b110;		/* Enable SCI0 on external pins and not only on LINPHY */
	}
}

/** Send a character through the selected SCI channel
 * 
 * 	@param character		Character to be send
 * 	@param sci_channel		SCI chañnnel that will send the character
 * */
void put_char(char character, unsigned int sci_channel){
	tSCI* pSCI = (tSCI*) sci_channel;
	
	while(pSCI->scisr1.bit.tdre == 0){};	/* check SCI transmit data register is empty */
	pSCI->scidrl.byte = character;			/* Send character */
	while(pSCI->scisr1.bit.tc == 0){};		/* Wait for transmit complete flag to be set */		
}

/** Function that waits until a character is received through the selected SCI channel
 * 
 * @param sci_channel	SCI channel that will receive the character
 * @return	Value of the received character
 * */
char get_char(unsigned int sci_channel){
	tSCI* pSCI = (tSCI*) sci_channel;
	
	while(pSCI->scisr1.bit.rdrf == 0){};				/* check SCI receive data register full flag */
	return(pSCI->scidrl.byte);	
}

/** Sends a string through the desired channel
 * 
 * 	@param string		String to be send
 * 	@param sci_channel	SCI channel through which the string will be sent
 * */
void send_string(char string[], unsigned int sci_channel){
	int i;
	for(i = 0; string[i] != 0; ++i){				/* Send until the NULL character is reached */
		put_char(string[i], sci_channel);
	}
}
/** @}*/
