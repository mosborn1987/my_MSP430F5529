#include <msp430.h>
#include <UART.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	UART_init();

	Print_String("HI, HOW ARE YOU DOING?");


	while(1){}

}

