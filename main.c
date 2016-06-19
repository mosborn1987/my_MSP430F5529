//#include "driverlib.h"
#include <wdt_a.h>
//#include <test_spi.h>
//#include <DigiPot.h>
//#include <my_Nokia_5110.h>
//#include <Nokia_Test.h>
#include <ESP8266.h>
#include <UART_TERMINAL_A1.h>
#include <UART_A0.h>


//DHT22 dht (DHT_PIN);
//void time_delay(uint8_t delay_cycles);



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);



    ESP8266_setup();

}




