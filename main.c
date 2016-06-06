#include "driverlib.h"
#include <DigiPot.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    init_SPI_B0();
    POT_write_data(0x3F);
    while(1)
    {

    };
//    POT_DEMO();








}




