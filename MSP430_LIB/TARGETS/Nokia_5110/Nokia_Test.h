/*
 * Nokia_Test.h
 *
 *  Created on: Jun 10, 2016
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_
#define MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_

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
	// Send Command to
	sent_tx(&DIGI_POT.SS_GPIO, m_write);

}

void POT_init(void)
{
	// Initiate the Slave Select Pin
	init_SLAVE(&DIGI_POT);//SS_GPIO_DIGI_POT);

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

}




#endif /* MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_ */
