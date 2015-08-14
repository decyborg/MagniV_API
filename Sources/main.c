#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"


#define BUS_CLOCK	25000000

void main(void) {
	spi_divider spi;
	unsigned long delay;
  EnableInterrupts;
  clock_init(BUS_CLOCK);
  //sci_init(9600, BUS_CLOCK, SCI0);
  //send_string("Testing SCI module", SCI0);
  spi_init_mst(BUS_CLOCK, 2500000);
  
  for(;;) {
	  //put_char('A', SCI0);
	  send_SPI(0x55);
	  for(delay = 0; delay < 500000; ++delay);
  } /* loop forever */
  /* please make sure that you never leave main */
}
