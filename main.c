#include "driverlib.h"
#include <usci_a_uart.h>
#include <msp430.h>
#include <msp430f5529.h>
#include <intrinsics.h>

int main(void) {

	int BAUD_RATE = 9600;
	uint16_t PRESCALE_CLOCK_DIVIDER = 1;
    WDT_A_hold(WDT_A_BASE);


	if ( STATUS_FAIL == USCI_A_UART_init (
			__MSP430_BASEADDRESS_USCI_A0__,
			USCI_A_UART_CLOCKSOURCE_ACLK,
			PRESCALE_CLOCK_DIVIDER,
			UCS_getSMCLK(),//FIRST MOD
			BAUD_RATE,//SECOND MOD
			USCI_A_UART_NO_PARITY,//PARITY
			USCI_A_UART_LSB_FIRST,//MSB OR LSB
			USCI_A_UART_ONE_STOP_BIT, // STOP BITS
			USCI_A_UART_MODE, // UART MODE
			USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION))

	{
		return;
	}



	//Enable UART module for operation
	UART_enable (__MSP430_BASEADDRESS_USCI_A0__);

	//Enable Receive Interrupt
	UART_enableInterrupt (__MSP430_BASEADDRESS_USCI_A0__, UCRXIE);

	//Transmit data
	UART_transmitData(__MSP430_BASEADDRESS_USCI_A0__, transmitData++);

	// Enter LPM3, interrupts enabled
	__bis_SR_register(LPM3_bits + GIE);
	__no_operation();
}


//******************************************************************************
//
// This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
switch(__even_in_range(UCA0IV,4))
{
// Vector 2 - RXIFG
case 2:
// Echo back RXed character, confirm TX buffer is ready first
// USCI_A0 TX buffer ready?
while (!UART_interruptStatus(__MSP430_BASEADDRESS_USCI_A0__,
UCTXIFG)
);
//Receive echoed data
receivedData = UART_receiveData(__MSP430_BASEADDRESS_USCI_A0__);
//Transmit next data
UART_transmitData(__MSP430_BASEADDRESS_USCI_A0__,
transmitData++
);
break;
default: break;
}
}
