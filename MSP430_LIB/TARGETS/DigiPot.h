/*
 * DigiPot.h
 *
 *  Created on: May 31, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_DIGIPOT_H_
#define DRIVERLIB_DIGIPOT_H_

#include <USCI_B0_SPI.h>

#define DIGI_POT_DATA_BYTE_SIZE     0x02
#define DIGI_POT_MAX_BAUD_RATE      9600
#define COMMAND_DIGI_POT_READ       0x00
#define COMMAND_DIGI_POT_WRITE      0x11
#define COMMAND_DIGI_POT_SHUT_DOWN  0x21

TARGET_DEVICE DIGI_POT = {
		{ GPIO_PORT_P1, GPIO_PIN6, ACTIVE_LOW},
		{COMMAND_DIGI_POT_READ, COMMAND_DIGI_POT_WRITE, COMMAND_DIGI_POT_SHUT_DOWN},
		{DIGI_POT_DATA_BYTE_SIZE, DIGI_POT_MAX_BAUD_RATE, 10},
		SPI_B0

};

void POT_init(void);
void POT_write_data(uint8_t m_write);
void POT_shut_off();
void POT_DEMO(void);

void POT_write_data(uint8_t m_write)
{

//	send_COMMAND_AND_DATA()
	// Send Command to
	sent_tx(&DIGI_POT, m_write);

}

void POT_init(void)
{
	// Initiate the Slave Select Pin
	init_SLAVE(&DIGI_POT);//SS_GPIO_DIGI_POT);

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

}

void POT_DEMO(void)
{
	POT_init();

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
			POT_write_data(transmitData);

			// TIME DELAY
			__delay_cycles(10000);
			__delay_cycles(10000);
		}

		while(transmitData++ != high_value )
		{
			// TRANSMIT DATA
			sent_tx(&DIGI_POT, transmitData);
			POT_write_data(transmitData);

			// TIME DELAY
			__delay_cycles(10000);
			__delay_cycles(10000);

		}
}
}

#endif /* DRIVERLIB_DIGIPOT_H_ */
