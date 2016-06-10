//#include "driverlib.h"
#include <wdt_a.h>
//#include <test_spi.h>
#include <DigiPot.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
//    init_SPI_B0();

    POT_DEMO();
    while(1)
    {
    	POT_write_data(0x15);
    	POT_write_data(0x3F);
    	POT_write_data(0x70);

    };
//    POT_DEMO();








}




