/*
 * UART.h
 *
 *  Created on: Sep 1, 2015
 *      Author: Mario Osborn
 *
 *      Note: Example included at the bottom
 */

#ifndef MSP430_LIB_UART_TERMINAL_A1_H_
#define MSP430_LIB_UART_TERMINAL_A1_H_

// Contains 'sprintf'
#include <stdio.h>
#include <string.h>
#include <ISR_UART.h>
#include <usci_a_uart.h>

///////////////////////////////////////////////////////////////////
// Declare buffer size and data type
//unsigned char UART_buffer[100] = "hello_world";

void print_UART_buffer(void)
{
//	UART_TERMINAL_Enter();
//	UART_TERMINAL_Print_String_NL(UART_buffer);
//	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));

	// Send formatted buffer to UART
	UART_TERMINAL_SendArray(&UART_buffer, buffer_index);//strlen(UART_buffer));

	// Add a '\n\r' to the end of a line
	UART_TERMINAL_Enter();

	reset_UART_buffer_index();
}


////////////////////////////////////////////////////////////////////////
// Function Declaration - Each Function prototype is defined later
void UART_TERMINAL_init(void);
void UART_TERMINAL_get_array( unsigned char *RxArray, unsigned char number_of_chars);
char UART_TERMINAL_get_single_char(void);
void UART_TERMINAL_SendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UART_TERMINAL_SendChar( unsigned char);
void UART_TERMINAL_Test( void );

void UART_TERMINAL_Print_String(const char *my_Char);
void UART_TERMINAL_Print_String_NL(const char *my_Char);
void UART_TERMINAL_Enter(void);
void UART_TERMINAL_System_Bell(void);

void set_clock_baud_A1_9600(void);
void set_clock_baud_A1_115200(void);

void set_clock_baud_A1_9600(void)
{
	//Baudrate = 115200, clock freq = 1.048MHz
	//UCBRx = 9, UCBRFx = 0, UCBRSx = 2, UCOS16 = 0

	USCI_A_UART_initParam param = {0};
	param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
	//	9600(109) , 57600(18) or 115200(9) or 74880(14)

	param.clockPrescalar = 9;
	param.firstModReg = 0;
	param.secondModReg = 2;
	param.parity = USCI_A_UART_NO_PARITY;
	param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
	param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
	param.uartMode = USCI_A_UART_MODE;
	param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

	if(STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param))
	{
		return;
	}

}

void set_clock_baud_A1_115200(void)
{
	//Baudrate = 115200, clock freq = 1.048MHz
	//UCBRx = 9, UCBRFx = 0, UCBRSx = 2, UCOS16 = 0

	USCI_A_UART_initParam param = {0};
	param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
	param.clockPrescalar = 9;
	param.firstModReg = 0;
	param.secondModReg = 2;
	param.parity = USCI_A_UART_NO_PARITY;
	param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
	param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
	param.uartMode = USCI_A_UART_MODE;
	param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

	if(STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param))
	{
		return;
	}

}

////////////////////////////////////////////////////////////////////////
// Configure clocks and hardware needed for the UART
void UART_TERMINAL_init(void)
{
	set_clock_baud_A1_9600();
//	set_clock_baud_A1_115200();

	////////////////////////////////////////////////////////////////////
	//
	P4SEL = BIT5+BIT4; // P4.4, P4.5 = USCI_A0 TXD/RXD
//	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
//	UCA1CTL1 |= UCSSEL_2; // SMCLK
//	UCA1BR0 = 6; // 1MHz 9600 (see User's Guide)
//	UCA1BR1 = 0; // 1MHz 9600
//	UCA1MCTL = UCBRS_0 + UCBRF_13 + UCOS16; // Modln UCBRSx=0, UCBRFx=0,

	// over sampling
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	UCA1IE |= UCRXIE; // Enable USCI_A1 RX interrupt

//	print_UART_buffer();
//	print_UART_buffer();

    UART_TERMINAL_Print_String_NL("The UART Terminal A1 has been initialized:");

	return;
}

////////////////////////////////////////////////////////////////////////
// Get an array of chars via pass by reference.
void UART_TERMINAL_get_array(unsigned char *RxArray, unsigned char number_of_chars)
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
char UART_TERMINAL_get_single_char(void)
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
void UART_TERMINAL_SendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
	////////////////////////////////////////////////////////////////////
	// Prints the specified amount of chars
	while(ArrayLength--)
	{
		////////////////////////////////////////////////////////////////
		// Waits until the TX buffer is ready to recieve new data
		while (!(UCA1IFG&UCTXIFG)); // USCI_A0 TX buffer ready?

		////////////////////////////////////////////////////////////////
		// Write the character at the location specified py the pointer
		UCA1TXBUF = *TxArray;

		////////////////////////////////////////////////////////////////
		// Increment the TxArray pointer to point to the next character
		TxArray++;

	}

	return;

}


////////////////////////////////////////////////////////////////////////
// Send a single char value. Pass by value.
void UART_TERMINAL_SendChar( unsigned char send_char)
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
void UART_TERMINAL_Test(void)
{

	int Test_Number = 1;
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "UART TEST #%d\n\r",Test_Number );

	// Send formatted buffer to UART
	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));

}

void UART_TERMINAL_Print_String(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));

}

void UART_TERMINAL_Print_String_NL(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));

	// Add a '\n\r' to the end of a line
	UART_TERMINAL_Enter();

}

void UART_TERMINAL_Enter(void)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "\n\r\0");

	// Send formatted buffer to UART
	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));
}

#define bell_sound 7

void UART_TERMINAL_System_Bell(void)
{
	UART_TERMINAL_SendChar(bell_sound);
}

//////////////////////////////////////////////////////////////////////
// Example
//void UART_GREATER(void)
//{
//
//	///////////////////////////////////////////////////////////////////
//	// Format buffer with string
//	sprintf( UART_buffer, "GREATER\n\r");
//
//	// Send formatted buffer to UART
//	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));
//}

//////////////////////////////////////////////////////////////////////
// Example
//void UART_LESS(void)
//{
//
//	///////////////////////////////////////////////////////////////////
//	// Format buffer with string
//	sprintf( UART_buffer, "LESS\n\r");
//
//	// Send formatted buffer to UART
//	UART_TERMINAL_SendArray(&UART_buffer, strlen(UART_buffer));
//}



#endif /* MSP430_LIB_UART_TERMINAL_A1_H_ */
