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
#include <string.h>
#include <ISR_UART.h>
#include <usci_a_uart.h>

////////////////////////////////////////////////////////////////////////
// Function Declaration - Each Function prototype is defined later
void UART_init(long m_baud);
void UART_get_array( unsigned char *RxArray, unsigned char number_of_chars);
char UART_get_single_char(void);
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UARTSendChar( unsigned char);
void UART_Test( void );

void Print_String(const char *my_Char);
void Print_String_NL(const char *my_Char);

uint8_t calc_clockPrescalar(long baud);
uint8_t calc_clockPrescalar(long baud)
{
	//	9600(109) , 57600(18) or 115200(9) or 74880(14)

	// 9600 Baud
	if(baud == 9600)
	{
		return 109;
	}
	else if(baud == 57600)
	{
		return 18;
	}
	else if(baud == 115200)
	{
		return 9;
	}
	else
	{
		return (1048000/baud);
	}



}


void set_clock_settings_A0(long baud_rate);

void set_clock_settings_A0(long baud_rate)
{
	//Baudrate = 115200, clock freq = 1.048MHz 1,048,000
	//UCBRx = 9, UCBRFx = 0, UCBRSx = 2, UCOS16 = 0

	USCI_A_UART_initParam param_A0 = {0};
	param_A0.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;

	// 9600(109) , 57600(18) or 115200(9)
	param_A0.clockPrescalar = calc_clockPrescalar(baud_rate);
	param_A0.firstModReg = 0;
	param_A0.secondModReg = 2;
	param_A0.parity = USCI_A_UART_NO_PARITY;
	param_A0.msborLsbFirst = USCI_A_UART_LSB_FIRST;//USCI_A_UART_MSB_FIRST;//USCI_A_UART_LSB_FIRST;
	param_A0.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
	param_A0.uartMode = USCI_A_UART_MODE;
	param_A0.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

	if(STATUS_FAIL == USCI_A_UART_init(USCI_A0_BASE, &param_A0))
	{
		return;
	}

}

////////////////////////////////////////////////////////////////////////
// Configure clocks and hardware needed for the UART
void UART_init(long m_baud)
{
	set_clock_settings_A0(m_baud);

	////////////////////////////////////////////////////////////////////
	//
	P3SEL = BIT3 +BIT4;// P3.3 TXD/P3.4 RXD

	// over sampling
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	UCA0IE |= UCRXIE; // Enable USCI_A1 RX interrupt

	UART_TERMINAL_Print_String_NL("UART A0 Initialized:");

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
		*RxArray = UCA0RXBUF;//data;

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
	UCA0TXBUF = send_char;

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
//	UART_Enter();

	// This ending if spacific to the ESP2866
//	sprintf( UART_buffer, "\n\r\0"); // UART Message "ERROR" is returned
	sprintf( UART_buffer, "\r\n"); // NO UART Message is returned.

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

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
