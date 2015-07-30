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

#include "cpmu.h"

/** Initializes the Bus clock at the desired speed using the internal oscillator.
 * 
 * 	@param[in] BusClock Desired Bus Clock Frequency in hertz
 * 	
 * */
void clock_init(unsigned long BusClock){
	clock_dividers prescalers;
	prescalers = calc_prs(BusClock*2, FALSE, 0);
	set_clock(prescalers, FALSE);
}

/** Initializes the Bus clock at the desired speed using an external oscillator.
 * 
 * 	@param[in] BusClock Desired Bus Clock Frequency in hertz
 * 	@param[in] ExtFreq  Frequency of the external oscillator
 * */
void clock_init_ext(unsigned long BusClock, unsigned long ExtFreq){
	clock_dividers prescalers;
	prescalers = calc_prs(BusClock*2, TRUE, ExtFreq);
	set_clock(prescalers, TRUE);
}

/** Calculate the prescaler values for the corresponding bus frequency.
 * 
 * @param[in] FPLL Desired PLL frequency (bus frequency * 2) in hertz
 * @param[in] ExtClock If an External oscillator is being used set this variable to TRUE (1) otherwise set to FALSE (0)
 * @param[in] ExtFreq  If an oscillator is being used pass the frequency of the oscillator, otherwise pass FALSE (0)
 * 
 * @return A structure with the values of the prescalers
 * 
 * */
clock_dividers calc_prs(unsigned long FPLL, unsigned char ExtClock, unsigned long ExtFreq){
	clock_dividers prs;
	unsigned long Fref;
	
	/* Check if an external oscillator is being used */
	if(ExtClock == TRUE){
		if(!(ExtFreq % IRC)){	/* Check if ExtFreq is an integer multiple of IRC */
			prs.refdiv = (ExtFreq / IRC) - 1;	/* Fref = Fosc / (REFDIV + 1) */
			Fref = IRC;
		} // TODO if not select the best Fref (integer multiple for FVCO)
		
		prs.reffrq = SELECT_REF_RANGE(Fref);
	} else
		Fref = IRC;
	
	/* Check if Fpll = Fvco is possible */
	if((FPLL >= VCO_MIN) && (FPLL <= VCO_MAX)){
		//TODO check for not an exact frequency
		prs.postdiv = 0;		/* FPLL = FVCO / (POSTDIV + 1) -> FPLL = FVCO */
		prs.syndiv = (FPLL / (2 * Fref)) - 1;
		prs.vcofrq = SELECT_VCO_RANGE(FPLL);
	} else{ 
		unsigned long search_VCO, error;
		unsigned int min_error = 0;
		clock_dividers min_prs_values;
		unsigned char PostDiv, SynDiv;
		/* Search for best prescaler values */
		for(SynDiv = 0; SynDiv <= SYNDIV_MAX; ++SynDiv)
			search_VCO == 2 * Fref * (SynDiv + 1);						/* Search through possible values of Fvco */
			if((search_VCO >= VCO_MIN) && (search_VCO <= VCO_MAX)){		/* If VCO is within range */
				for(PostDiv = 0; PostDiv <= POSTDIV_MAX; ++PostDiv){	/* Brute force through possible values of Postdiv for best match */
					error = (search_VCO / (PostDiv + 1));
					error = error - FPLL;
					if(error == 0){
						prs.postdiv = PostDiv;
						prs.syndiv = SynDiv;
						prs.vcofrq = SELECT_VCO_RANGE(search_VCO);
						return prs;
					} else {
						if(min_error == 0)								/* First time it enters the algorithm */
							min_error = error;
						if(error <= min_error){							/* The minimum possible error will be stored */
							min_error = error;							/* Update minimum error */
							prs.postdiv = PostDiv;						/* Store corresponding values */
							prs.syndiv = SynDiv;
							prs.vcofrq = SELECT_VCO_RANGE(search_VCO);
						}
					}
				}
			}
	}
	
	return prs;
}

/** Set the clock registers
 * 	
 * 	@param[in] ClockConfig Holds the prescaler values to configure the clock
 * 	@param[in] ExtClock If an External oscillator is being used set this variable to TRUE (1) otherwise set to FALSE (0)
 * */
void set_clock(clock_dividers ClockConfig, unsigned char ExtClock){
	//TODO implement portable version
	if(ExtClock == TRUE){
		CPMUOSC_OSCE = 1;
		CPMUREFDIV_REFDIV = ClockConfig.refdiv;
	} else {
		CPMUSYNR_VCOFRQ = ClockConfig.vcofrq;
		CPMUSYNR_SYNDIV = ClockConfig.syndiv;
		CPMUPOSTDIV_POSTDIV = ClockConfig.postdiv;
	}
	while(0 == CPMUIFLG_LOCK);
}
