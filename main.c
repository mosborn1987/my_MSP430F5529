//#include "driverlib.h"
#include <wdt_a.h>
//#include <test_spi.h>
//#include <DigiPot.h>
//#include <my_Nokia_5110.h>
//#include <Nokia_Test.h>
#include <ESP8266.h>
#include <UART_TERMINAL_A1.h>
#include <UART_A0.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // This also sets up UART A0 and A1
    ESP8266_setup();

    while(1)
    {
    	UART_TERMINAL_Print_String_NL("String Printed from UART_TERMINAL_A1.h");
    	Print_String_NL("This is being printed from UART_A0.h @115200 baud.");
    }

}




