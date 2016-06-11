/*
 * Nokia_Test.h
 *
 *  Created on: Jun 10, 2016
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_
#define MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_

#include <USCI_B0_SPI.h>
#include <PCD8544.h>
#include <stdio.h>

#include "boolean.h"
#include "delay.h"

#define NOKIA_5100_DATA_BYTE_SIZE   0x02
#define NOKIA_5100_MAX_BAUD_RATE    9600

TARGET_DEVICE NOKIA_5100 = {
		{ GPIO_PORT_P1, GPIO_PIN6, ACTIVE_LOW},
		{0,0,0},
		{NOKIA_5100_DATA_BYTE_SIZE, NOKIA_5100_MAX_BAUD_RATE, 10},
		SPI_B0
};

void NOKIA_5100_init(void);
void NOKIA_5100_execute_command(uint8_t m_command, uint8_t m_write);
void NOKIA_5100_DEMO(void);

void NOKIA_5100_init(void)
{
	// Initiate the Slave Select Pin
	init_SLAVE(&NOKIA_5100);//SS_GPIO_DIGI_POT);

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

	// Setup the LCD stuff.
	lcd_setup();
//	delay_ms(1);  // Just to make sure the LCD is ready
	lcd_init();
	lcd_clear();
}


void NOKIA_5100_execute_command(uint8_t m_command, uint8_t m_write)
{
	// Send the command than data to the POT
	send_COMMAND_AND_DATA(&NOKIA_5100, m_command, m_write);
}


void NOKIA_5100_DEMO(void)
{
	NOKIA_5100_init();

	// A simple string print.
	lcd_print("Hello Pacho!");

	// Another example string.
	lcd_set_pos(0, 1);  // Going to the second row.
	lcd_print("I loveU!");


	int times = 250;


	while (1)
	{
		lcd_set_pos(0, 2);
		lcd_print("m");

		int i = 0;
		for(i = 0; i < 5; i++)
		{
			lcd_print("e");

		}

		lcd_print("h /:(");
		lcd_clear_row(2);


	}
}







#endif /* MSP430_LIB_TARGETS_NOKIA_5110_NOKIA_TEST_H_ */
