/**
 *  test.c
 *  Test drive.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <stdio.h>
//#include <msp430g2553.h>
//#include <LPM_time_delay.h>
#include <msp430f5529.h>
#include "PCD8544.h"

#include "boolean.h"
#include "delay.h"

void init_Nokia_5110(void)
{

//	WDTCTL = WDTPW + WDTHOLD;  // Disable WDT.
//	BCSCTL1 = CALBC1_1MHZ;     // 1MHz clock.
//	DCOCTL = CALDCO_1MHZ;
//	BCSCTL2 &= ~(DIVS_3);      // SMCLK = DCO = 1MHz.

	// Setup the LCD stuff.
	lcd_setup();
//	delay_ms(1);  // Just to make sure the LCD is ready
	lcd_init();
	lcd_clear();

}

void infinite_LCD(void)
{
	// A simple string print.
	lcd_print("Hello Pacho!");

	// Another example string.
	lcd_set_pos(0, 1);  // Going to the second row.
	lcd_print("I loveU!");

	// A simple bar.
//	unsigned int i = 0;
//	lcd_set_pos(0, 1);
//	for (i = 0; i < 84; i++) {
//		lcd_command(0, 0b11111111);
////		delay_ms(10);
//	}

	// Clear just that row and write some text.
//	lcd_clear_row(1);
//	lcd_putc('@');  // If all you want is a single character.
//	lcd_print("nathanpc");

	int times = 250;


	while (1)
	{
		// And more text!
//		_LP_time_delay_s(2);
		lcd_set_pos(0, 2);
		lcd_print("m");
//		_LP_time_delay_ms(times);

//		lcd_print("TEST");

		int i = 0;
		for(i = 0; i < 5; i++)
		{
			lcd_print("e");
//			_LP_time_delay_ms(times);

		}

		lcd_print("h /:(");
//		_LP_time_delay_ms(times);
//		_LP_time_delay_s(1);
		lcd_clear_row(2);

//		lcd_set_pos(0, 2);
//		lcd_print("me");
//		_LP_time_delay_ms(times);
//
//		lcd_set_pos(0, 2);
//		lcd_print("meh");
//		_LP_time_delay_ms(times);
//
//		lcd_set_pos(0, 2);
//		lcd_print("mehh");
//		_LP_time_delay_ms(times);
//
//		lcd_set_pos(0, 2);
//		lcd_print("mehhh");
//		_LP_time_delay_ms(times);
//
//		lcd_set_pos(0, 2);
//		lcd_print("mehhhhh /:(");
//		_LP_time_delay_ms(500);

//		lcd_set_pos(0, 3);
//		lcd_print("Test");
//



//		lcd_print("Test 2");
//		_LP_time_delay_ms(500);
//		_LP_time_delay_s(2);
//		lcd_set_pos(0, 2);
//		lcd_print(" ");
//		_LP_time_delay_s(2);
//
//		init_Nokia_5110();
////		lcd_setup();
////		delay_ms(1);  // Just to make sure the LCD is ready
////		lcd_init();
//
//		lcd_set_pos(0, 2);
//		lcd_print("Test");
//		lcd_clear();

	}

}

