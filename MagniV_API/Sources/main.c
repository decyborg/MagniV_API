#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "cpmu.h"




void main(void) {

  EnableInterrupts;
  /* include your code here */

  clock_init(8000000);
  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
    
  } /* loop forever */
  /* please make sure that you never leave main */

}
