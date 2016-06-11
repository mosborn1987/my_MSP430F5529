//#include "driverlib.h"
#include <wdt_a.h>
//#include <test_spi.h>
#include <DigiPot.h>
#include <my_Nokia_5110.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

//    POT_init();
//    POT_write_data(0x35);
    POT_DEMO();
//    init_Nokia_5110();
//    infinite_LCD();



}




