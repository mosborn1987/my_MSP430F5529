//#include "driverlib.h"
#include <test_spi.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    init_pot();


}




