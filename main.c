//#include "driverlib.h"
#include <wdt_a.h>
//#include <test_spi.h>
//#include <DigiPot.h>
//#include <my_Nokia_5110.h>
//#include <Nokia_Test.h>
#include <ESP8266.h>
#include <UART.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    UART_init();
    while(1)
    {
    	Print_String_NL("UART IS WORKING!");
    }


}




