#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"


#define BUS_CLOCK	25000000

void main(void) {
	spi_divider spi;
  EnableInterrupts;
  clock_init(BUS_CLOCK);
  sci_init(9600, BUS_CLOCK, SCI0);
  send_string("Testing SCI module", SCI0);
  spi = spi_baud_cal(BUS_CLOCK, 2500000);
  
  for(;;) {
	  put_char('A', SCI0);
  } /* loop forever */
  /* please make sure that you never leave main */
}
