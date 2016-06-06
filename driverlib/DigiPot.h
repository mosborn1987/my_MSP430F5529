/*
 * DigiPot.h
 *
 *  Created on: May 31, 2016
 *      Author: Mario Osborn
 */

//*****************************************************************************
//! This example shows how SPI master talks to SPI slave using 3-wire mode.
//! Incrementing data is sent by the master starting at 0x01. Received data is
//! expected to be same as the previous transmission.  USCI RX ISR is used to
//! handle communication with the CPU, normally in LPM0. If high, P1.0 indicates
//! valid data reception.  Because all execution after LPM0 is in ISRs,
//! initialization waits for DCO to stabilize against ACLK.
//! ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//!
//! Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
//! slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//! "Release JTAG on Go" on slave device.  If breakpoints are set in
//! slave RX ISR, master must stopped also to avoid overrunning slave
//! RXBUF.
//!
//!                  MSP430F5438A
//!                 -----------------
//!            /|\ |                 |
//!             |  |                 |
//!    Master---+->|RST              |
//!                |                 |
//!                |             P3.1|-> Data Out (UCB0SIMO)
//!                |                 |
//!                |             P3.2|<- Data In (UCB0SOMI)
//!                |                 |
//!                |             P3.3|-> Serial Clock Out (UCB0CLK)
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - SPI peripheral
//! - GPIO Port peripheral (for SPI pins)
//! - UCB0SIMO
//! - UCB0SOMI
//! - UCB0CLK
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - USCI_A0_VECTOR
//!
//*****************************************************************************

#ifndef DRIVERLIB_DIGIPOT_H_
#define DRIVERLIB_DIGIPOT_H_

#include <test_spi.h>

#define potCommand = B00100001;         // command to shutdown pot

void POT_init(void);
void POT_write_data(uint8_t m_write);
void POT_shut_off();
void POT_DEMO(void);

void POT_write_data(uint8_t m_write)
{
	SLAVE_SELECT DIGI_POT = {
			DIGI_POT.PORT = GPIO_PORT_P1,
			DIGI_POT.PIN = GPIO_PIN6,
			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
	};

	init_SLAVE(&DIGI_POT);

	sent_tx(&DIGI_POT, m_write);

}

void POT_DEMO(void)
{
//	POT_init();

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();



	//    uint8_t POT_COMMAND = 0x11;// B00010001;
	uint8_t transmitData = 0x00;
	//Initialize data values
	uint8_t low_value = 0x10;
	uint8_t high_value = 0x7F;
	transmitData = high_value;

	// TEST WRITE
	while(1)
	{

		while(transmitData--!=low_value)
		{
			// TRANSMIT DATA
//			sent_tx(&DIGI_POT, transmitData);
			POT_write_data(transmitData);

			// TIME DELAY
			__delay_cycles(10000);
			__delay_cycles(10000);
		}

		while(transmitData++ != high_value )
		{
			// TRANSMIT DATA
//			sent_tx(&DIGI_POT, transmitData);
			POT_write_data(transmitData);

			// TIME DELAY
			__delay_cycles(10000);
			__delay_cycles(10000);

		}
}
}

void POT_init(void)
{
//	// INITIALIZE SPI CHANNEL B0
//	init_SPI_B0();
//
//	SLAVE_SELECT DIGI_POT = {
//			DIGI_POT.PORT = GPIO_PORT_P1,
//			DIGI_POT.PIN = GPIO_PIN6,
//			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
//	};
//
//    init_SLAVE(&DIGI_POT);


}

#endif /* DRIVERLIB_DIGIPOT_H_ */
