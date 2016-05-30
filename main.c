#include <msp430.h>
#include <UART.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	UART_init();

	char valueX[10];
	valueX[1]= UART_get_single_char();
	valueX[2] = UART_get_single_char();


	__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
	__no_operation(); // For debugger
}

