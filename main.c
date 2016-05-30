#include <msp430.h>
#include <UART.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	UART_init();

	Print_String("CHAR TO SEND: ");
	UARTSendChar('B');

	while(1){}

}

