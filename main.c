#include "driverlib.h"

int main(void) {

    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
    while(1)
    {
    	GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    	GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN7);
    	__delay_cycles(40000);
    	__delay_cycles(40000);
    	__delay_cycles(40000);

    }

    return (0);
}


