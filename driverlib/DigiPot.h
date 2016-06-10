/*
 * DigiPot.h
 *
 *  Created on: May 31, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_DIGIPOT_H_
#define DRIVERLIB_DIGIPOT_H_

#include <test_spi.h>

#define potCommand = B00100001;         // command to shutdown pot

void POT_init(void);
void POT_write_data(uint8_t m_write);
void POT_shut_off();
void POT_DEMO(void);

SLAVE_SELECT DIGI_POT = {
		GPIO_PORT_P1,
		GPIO_PIN6,
		ACTIVE_LOW
};

void POT_write_data(uint8_t m_write)
{

	init_SLAVE(&DIGI_POT);

	sent_tx(&DIGI_POT, m_write);

}

void POT_init(void)
{
	// Initiate the Slave Select Pin
	init_SLAVE(&DIGI_POT);

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

#endif /* DRIVERLIB_DIGIPOT_H_ */
