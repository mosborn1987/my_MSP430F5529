/*
 * time.h
 *
 *  Created on: Jun 15, 2016
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TIME_H_
#define MSP430_LIB_TIME_H_

void time_delay(uint8_t delay_cycles);
void time_delay(uint8_t delay_cycles)
{
	while(delay_cycles>0)
	{
    	_delay_cycles(30000);
    	_delay_cycles(30000);
    	_delay_cycles(30000);
    	_delay_cycles(30000);
    	_delay_cycles(30000);
    	_delay_cycles(30000);
    	delay_cycles--;
	}
}




#endif /* MSP430_LIB_TIME_H_ */
