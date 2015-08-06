#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "cpmu.h"


void main(void) {

  EnableInterrupts;
  clock_init(32000000);
    
  for(;;) {
		
  } /* loop forever */
  /* please make sure that you never leave main */
}
