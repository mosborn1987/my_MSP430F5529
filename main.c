//#include "driverlib.h"
#include <test_spi.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

	// INITIALIZE SPI CHANNEL B0
	init_SPI_B0();

	SLAVE_SELECT DIGI_POT = {
			DIGI_POT.PORT = GPIO_PORT_P1,
			DIGI_POT.PIN = GPIO_PIN6,
			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
	};

    init_pot(&DIGI_POT);

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




