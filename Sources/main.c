#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"


#define BUS_CLOCK	25000000

void main(void) {
	spi_divider spi;
	unsigned long delay;
	word spi_data;
  EnableInterrupts;
  clock_init(BUS_CLOCK);
  EnableClockOutput;
  //sci_init(9600, BUS_CLOCK, SCI0);
  //send_string("Testing SCI module", SCI0);
  //spi_init_mst(BUS_CLOCK, 2500000, BIT_16);
  spi_init_slv(BIT_16, SPI_MODE0);
  
  for(;;) {
	  //put_char('A', SCI0);
	  //send_SPI(0x5555);
	  spi_data = get_SPI();
	  for(delay = 0; delay < 500000; ++delay){};
  } /* loop forever */
  /* please make sure that you never leave main */
}
