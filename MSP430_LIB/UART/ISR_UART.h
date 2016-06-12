/*
 * ISR_UART.h
 *
 *  Created on: May 30, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_ISR_UART_H_
#define DRIVERLIB_ISR_UART_H_

//#include <UART.h>
////////////////////////////////////////////////////////////////////////
// Variable declaration
static volatile char data;


// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{

	switch(__even_in_range(UCA1IV,4))
	{
		case 0:break; // Vector 0 - no interrupt
		case 2: // Vector 2 - RXIFG
		while (!(UCA1IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
		UCA1TXBUF = UCA1RXBUF; // TX -> RXed character
		data = UCA1RXBUF;
		break;
		case 4:break; // Vector 4 - TXIFG
		default: break;
	}
	_BIC_SR(LPM0_EXIT);
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{

	switch(__even_in_range(UCA0IV,4))
	{
		case 0:break; // Vector 0 - no interrupt
		case 2: // Vector 2 - RXIFG
		while (!(UCA1IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
		UCA0TXBUF = UCA0RXBUF; // TX -> RXed character
		data = UCA0RXBUF;
		break;
		case 4:break; // Vector 4 - TXIFG
		default: break;
	}
	_BIC_SR(LPM0_EXIT);
}


#endif /* DRIVERLIB_ISR_UART_H_ */
