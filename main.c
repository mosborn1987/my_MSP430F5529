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

    //initiate the UART Terminal
//    UART_TERMINAL_init();

    ESP8266_setup();

//    // Place the MSP to slee and enable inturrputs
////    __bis_SR_register(LPM0_bits + GIE);
//   	////////////////////////////////////////////////////////////////////
//    	// Waits for the return of a single value from the UART. The
//    	// MSP430 will enter into LPM0;
//    	__bis_SR_register(GIE);
//
//    while(1)
//    {
//    	UART_TERMINAL_Print_String_NL("Type: ");
//    	time_delay(20);
////    	print_UART_buffer();
////    	UART_TERMINAL_SendArray(&UART_buffer, buffer_index);
////    	reset_UART_buffer_index();
//
////    	UART_TERMINAL_Print_String("CHAR Amount: ");
////    	UART_TERMINAL_SendChar(UART_DATA_AVALIABLE());
//    	UART_TERMINAL_SendChar(buffer_index);
//
//
////    	return data;
//    }

//    UART_TERMINAL_get_single_char();



    // This also sets up UART A0 and A1
//    ESP8266_setup();
//
//    while(1)
//    {
//    	UART_TERMINAL_Print_String_NL("String Printed from UART_TERMINAL_A1.h");
//    	Print_String_NL("This is being printed from UART_A0.h @115200 baud.");
//    }

}




