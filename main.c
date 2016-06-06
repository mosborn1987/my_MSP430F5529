//#include "driverlib.h"
#include <test_spi.h>



void main(void)
{
    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

	SLAVE_SELECT DIGI_POT = {
			DIGI_POT.PORT = GPIO_PORT_P1,
			DIGI_POT.PIN = GPIO_PIN6,
			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
	};

    init_pot(&DIGI_POT);


}




