/*
 * ESP8266.h
 *
 *  Created on: Jun 10, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_
#define DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_

#include <USCI_B0_SPI.h>

void POT_init(void);
void POT_write_data(uint8_t m_write);
void POT_shut_off();
void POT_DEMO(void);

SLAVE_SELECT_GPIO DIGI_POT = {
		GPIO_PORT_P1,
		GPIO_PIN6,
		ACTIVE_LOW
};

void POT_write_data(uint8_t m_write)
{
	// Send Command to
	sent_tx(&DIGI_POT, m_write);

}

void POT_init(void)
{
	// Initiate the Slave Select Pin
	init_SLAVE(&DIGI_POT);

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

}

#endif /* DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_ */
