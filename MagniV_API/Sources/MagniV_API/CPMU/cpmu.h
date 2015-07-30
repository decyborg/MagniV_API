/**
 *  @file cpmu.h
 *
 * 	@brief Contains Clock and power management unit API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */

#ifndef CPMU_H_
#define CPMU_H_

/* Include derivative support */
#include "derivative.h"
#include "common.h"

/* Global definitions */
#define IRC 1000000	/* Internal Reference Clock */

/* Typedefs */
/** A structure that holds the divider values for the clock configuration. 
 * 	
 * */
typedef struct {
	unsigned char  syndiv;	/**< Multiplier to the Fvco, Fvco = 2*Fref*(syndiv+1)*/
	unsigned char  postdiv; /**< Divider for Fpll, Fpll = Fvco /(postdiv + 1) */
	unsigned char  refdiv;	/**< Divider for Fref (only used with an external oscillator), Fref = Fosc /(refdiv + 1) */
	unsigned char  reffrq;  /**< Reference clock range selection */
	unsigned char  vcofrq;	/**< VCO clock frequency range selection */
}clock_dividers;

/* Prototypes */
void clock_init(unsigned long BusClock);
void clock_init_ext(unsigned long BusClock, unsigned long ExtFreq);
clock_dividers calc_prs(unsigned long FPLL, unsigned char ExtClock, unsigned long ExtFreq);
void set_clock(clock_dividers ClockConfig, unsigned char ExtClock);

#if (defined(_MC9S12ZVL32_H)) /* S12ZVL32 specific definitions */
#define VCO_MIN 32000000
#define VCO_MID 48000000
#define VCO_MAX 64000000
#define VCO_STEP 1000000
#define POSTDIV_MAX 31
#define SYNDIV_MAX 63
#define REF_MIN_TH1 1000000
#define REF_MIN_TH2 2000000
#define REF_MID_TH  6000000
#define REF_MAX_TH 12000000
#define SELECT_VCO_RANGE(x) (x <= VCO_MID)? 0 : 1 
#define SELECT_REF_RANGE(x) ( (((x >= REF_MIN_TH1) && (x <= REF_MIN_TH2))? 0 : 1) ^ ((x <= REF_MID_TH)? 0 : 3) | ((x <= REF_MAX_TH)? 0 : 1))
#endif /* END of S12ZVL32 specific definitions */

#endif /* CPMU_H_ */
