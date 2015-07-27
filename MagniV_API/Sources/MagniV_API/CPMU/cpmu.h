/*
 * cpmu.h
 *
 *  Created on: Jul 24, 2015
 *      Author: B52932
 */

#ifndef CPMU_H_
#define CPMU_H_

/* Typedefs */
typedef struct {
	unsigned char  syndiv;
	unsigned char  postdiv;
	unsigned char  refdiv;
}clock_dividers;

/* Prototypes */
void clock_init(unsigned long BusClock);
clock_dividers PLL(unsigned long FPLL);



#endif /* CPMU_H_ */
