#include "driverlib.h"
#include <DigiPot.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    POT_DEMO();








}




