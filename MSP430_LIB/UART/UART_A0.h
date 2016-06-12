/*
 * UART_A0.h
 *
 *  Created on: Jun 11, 2016
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_UART_A0_H_
#define MSP430_LIB_UART_A0_H_

// Contains 'sprintf'
#include <stdio.h>
#include <ISR_UART.h>

////////////////////////////////////////////////////////////////////////
// Function Declaration - Each Function prototype is defined later
void UART_init(void);
void UART_get_array( unsigned char *RxArray, unsigned char number_of_chars);
char UART_get_single_char(void);
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UARTSendChar( unsigned char);
void UART_Test( void );

void Print_String(const char *my_Char);
void Print_String_NL(const char *my_Char);

////////////////////////////////////////////////////////////////////////
// Configure clocks and hardware needed for the UART
void UART_init(void)
{
	////////////////////////////////////////////////////////////////////
	//

//	P4SEL = BIT5+BIT4; // P4.4, P4.5 = USCI_A0 TXD/RXD
	P3SEL = BIT3 +BIT4;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 6; // 1MHz 9600 (see User's Guide)
	UCA0BR1 = 0; // 1MHz 9600
	UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16; // Modln UCBRSx=0, UCBRFx=0,

	// over sampling
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	UCA0IE |= UCRXIE; // Enable USCI_A1 RX interrupt

	return;
}

////////////////////////////////////////////////////////////////////////
// Get an array of chars via pass by reference.
void UART_get_array(unsigned char *RxArray, unsigned char number_of_chars)
{
	////////////////////////////////////////////////////////////////////
	// Iterative method of retriving chars
	while(number_of_chars != 0)
	{
		//////////////////////////////////////////////////////////////
		// Waits for the return of a single value from the UART. The
		// MSP430 will enter into LPM0;
		__bis_SR_register(LPM0_bits + GIE);

		//////////////////////////////////////////////////////////////
		// Return data to the pointed locations
		*RxArray = data;

		//////////////////////////////////////////////////////////////
		// Increments the array pointer value
		RxArray++;

		//////////////////////////////////////////////////////////////
		// decrement the remaining charachter to retrive
		number_of_chars--;
	}

	return;

}

////////////////////////////////////////////////////////////////////////
// Return by value single char
char UART_get_single_char(void)
{
	////////////////////////////////////////////////////////////////////
	// Waits for the return of a single value from the UART. The
	// MSP430 will enter into LPM0;
	__bis_SR_register(LPM0_bits + GIE);

	return data;

}


////////////////////////////////////////////////////////////////////////
// Retriveds data from RX and echos the result to console
//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void USCI0RX_ISR(void)
//{
//	////////////////////////////////////////////////////////////////////
//	// Retrive data from the UCA0RXBUF and stores it in variable 'data'
//	data = UCA0RXBUF;
//
//	////////////////////////////////////////////////////////////////////
//	// Echo value to console
//	UARTSendArray(&data, 1);
//
//	////////////////////////////////////////////////////////////////////
//	// Exits LOW Power Mode
//	_BIC_SR(LPM0_EXIT);
//
//	////////////////////////////////////////////////////////////////////
//	// Disables Global Interrupts
//	_DINT();
//
//}


////////////////////////////////////////////////////////////////////////
// Print array or string in 'single quote' notation.
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
	////////////////////////////////////////////////////////////////////
	// Prints the specified amount of chars
	while(ArrayLength--)
	{
		////////////////////////////////////////////////////////////////
		// Waits until the TX buffer is ready to recieve new data
		while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?

		////////////////////////////////////////////////////////////////
		// Write the character at the location specified py the pointer
		UCA0TXBUF = *TxArray;

		////////////////////////////////////////////////////////////////
		// Increment the TxArray pointer to point to the next character
		TxArray++;

	}

	return;

}


////////////////////////////////////////////////////////////////////////
// Send a single char value. Pass by value.
void UARTSendChar( unsigned char send_char)
{
	////////////////////////////////////////////////////////////////
	// Waits until the TX buffer is ready to recieve new data
//	while(!(IFG2 & UCA0TXIFG));

	////////////////////////////////////////////////////////////////////
	// Writes the passed value to the UART buffer
	UCA1TXBUF = send_char;

	return;

}


//////////////////////////////////////////////////////////////////////
// Example
void UART_Test(void)
{

	int Test_Number = 1;
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "UART TEST #%d\n\r",Test_Number );

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

}

void Print_String(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

}

void Print_String_NL(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

	// Add a '\n\r' to the end of a line
	UART_Enter();

}

void UART_Enter(void)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "\n\r\0");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}

#define bell_sound 7

void System_Bell(void)
{
	UARTSendChar(bell_sound);
}

//////////////////////////////////////////////////////////////////////
// Example
void UART_GREATER(void)
{

	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "GREATER\n\r");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}

//////////////////////////////////////////////////////////////////////
// Example
void UART_LESS(void)
{

	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "LESS\n\r");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}


#endif /* MSP430_LIB_UART_A0_H_ */
