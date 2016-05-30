#include <msp430.h>
#include <UART.h>
#include <stdio.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	UART_init();

	UART_get_array(10, UART_buffer);
	UARTSendArray(UART_buffer, 10);
//
//	UART_buffer[] = "Hello World!";
//	sprintf(UART_buffer, "hello world!n");
//	UARTSendArray(UART_buffer, 12);
//	UARTSendArray(UART_buffer, 12);

	__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
	__no_operation(); // For debugger
}

