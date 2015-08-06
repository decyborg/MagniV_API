#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"


#define BUS_CLOCK	25000000

void main(void) {

  EnableInterrupts;
  clock_init(BUS_CLOCK);
  sci_init(9600, BUS_CLOCK, SCI0);
  send_string("Testing SCI module", SCI0);
  
  for(;;) {
	  put_char('A', SCI0);
  } /* loop forever */
  /* please make sure that you never leave main */
}
