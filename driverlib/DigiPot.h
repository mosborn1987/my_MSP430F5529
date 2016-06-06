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
void POT_write_data();
void POT_shut_off();
void POT_DEMO(void);

void POT_DEMO(void)
{
//	POT_init();

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

	SLAVE_SELECT DIGI_POT = {
			DIGI_POT.PORT = GPIO_PORT_P1,
			DIGI_POT.PIN = GPIO_PIN6,
			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
	};

    init_SLAVE(&DIGI_POT);
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
			sent_tx(&DIGI_POT, transmitData);

			// TIME DELAY
			__delay_cycles(10000);
			__delay_cycles(10000);
		}

		while(transmitData++ != high_value )
		{
			// TRANSMIT DATA
			sent_tx(&DIGI_POT, transmitData);

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
