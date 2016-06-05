/*
 * test_spi.h
 *
 *  Created on: Jun 5, 2016
 *      Author: Mario Osborn
 */

//*****************************************************************************
//! This example shows how SPI master talks to SPI slave using 3-wire mode.
//! Incrementing data is sent by the master starting at 0x01. Received data is
//! expected to be same as the previous transmission.  USCI RX ISR is used to
//! handle communication with the CPU, normally in LPM0. If high, P1.0 indicates
//! valid data reception.  Because all execution after LPM0 is in ISRs,
//! initialization waits for DCO to stabilize against ACLK.
//! ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//!
//! Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
//! slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//! "Release JTAG on Go" on slave device.  If breakpoints are set in
//! slave RX ISR, master must stopped also to avoid overrunning slave
//! RXBUF.
//!
//!                  MSP430F5438A
//!                 -----------------
//!            /|\ |                 |
//!             |  |                 |
//!    Master---+->|RST              |
//!                |                 |
//!                |             P3.1|-> Data Out (UCB0SIMO)
//!                |                 |
//!                |             P3.2|<- Data In (UCB0SOMI)
//!                |                 |
//!                |             P3.3|-> Serial Clock Out (UCB0CLK)
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - SPI peripheral
//! - GPIO Port peripheral (for SPI pins)
//! - UCB0SIMO
//! - UCB0SOMI
//! - UCB0CLK
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - USCI_A0_VECTOR
//!
//*****************************************************************************

#ifndef DRIVERLIB_TEST_SPI_H_
#define DRIVERLIB_TEST_SPI_H_

#include "driverlib.h"
//*****************************************************************************
//
//Specify desired frequency of SPI communication
//
//*****************************************************************************
#define SPICLK                          500000

enum CS_ACTIVE_VALUE{
	ACTIVE_LOW,
	ACTIVE_HIGH
};

typedef struct SLAVE_SELECT{
	uint8_t PORT;
	uint16_t PIN;
	int SS_ACTIVE_VALUE;
}SLAVE_SELECT;



uint8_t transmitData = 0x00, receiveData = 0x00;
uint8_t returnValue = 0x00;
void set_SLAVE_HIGH(SLAVE_SELECT *PARAM);
void set_SLAVE_LOW(SLAVE_SELECT *PARAM);
void init_pot(void);

void enable_SLAVE(SLAVE_SELECT *PARAM);
void disable_SLAVE(SLAVE_SELECT *PARAM);

void enable_SLAVE(SLAVE_SELECT *PARAM)
{

	// IF SLAVE IS ACTIVE HIGH, BRING THE CHIP LOW - TO DISABLE
	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_HIGH)
	{
		set_SLAVE_HIGH(PARAM);
	}

	// ELSE IF THE SLAVE IS ACTIVE LOW, BRING THE CHIP HIGH - TO DISABLE
	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_LOW)
	{
		set_SLAVE_LOW(PARAM);
	}
	return;


}

void disable_SLAVE(SLAVE_SELECT *PARAM)
{


	// IF SLAVE IS ACTIVE HIGH, BRING THE CHIP LOW - TO DISABLE
	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_HIGH)
	{
		set_SLAVE_LOW(PARAM);
	}

	// ELSE IF THE SLAVE IS ACTIVE LOW, BRING THE CHIP HIGH - TO DISABLE
	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_LOW)
	{
		set_SLAVE_HIGH(PARAM);
	}
	return;

}

void set_SLAVE_HIGH(SLAVE_SELECT *PARAM)
{
	//Set P1.1 for slave reset
	    GPIO_setOutputHighOnPin(
	        GPIO_PORT_P1,
	        GPIO_PIN6
	        );
}

void set_SLAVE_LOW(SLAVE_SELECT *PARAM)
{
    //Now with SPI signals initialized, reset slave
    GPIO_setOutputLowOnPin(
        PARAM->PORT,
        PARAM->PIN
        );
}



void init_pot(void)
{

	SLAVE_SELECT DIGI_POT = {
			DIGI_POT.PORT = GPIO_PORT_P1,
			DIGI_POT.PIN = GPIO_PIN6,
			DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
	};


    //Set P1.1 for slave reset
    //Set P1.0 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN6
        );

    //P3.0(UCB0SIMO), P3.1(UCB0SOMI) AND P3.2(UCB0CLK)	// P3.5,4,0 option select
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN0
        );

    //Initialize Master
    USCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = UCS_getSMCLK();
    param.desiredSpiClock = SPICLK;
    param.msbFirst = USCI_B_SPI_MSB_FIRST;
    param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    returnValue = USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

    if(STATUS_FAIL == returnValue)
    {
        return;
    }

    //Enable SPI module
    USCI_B_SPI_enable(USCI_B0_BASE);

    //Enable Receive interrupt
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_enableInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);

    //Now with SPI signals initialized, reset slave
//    GPIO_setOutputLowOnPin(
//        GPIO_PORT_P1,
//        GPIO_PIN6
//        );

    set_SLAVE_HIGH(&DIGI_POT);
    enable_SLAVE(&DIGI_POT);
//    //LED On
//    GPIO_setOutputHighOnPin(
//        GPIO_PORT_P1,
//        GPIO_PIN0
//        );

    //Wait for slave to initialize
    __delay_cycles(100);


    uint8_t POT_COMMAND = 0x11;// B00010001;
    //Initialize data values
    uint8_t low_value = 0x10;
    uint8_t high_value = 0x7F;
    transmitData = high_value;
    while(1)
    {

    	while(transmitData--!=low_value)
    	{
    		enable_SLAVE(&DIGI_POT);
    	    //USCI_A0 TX buffer ready?
    	    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
    	                                         USCI_B_SPI_TRANSMIT_INTERRUPT))
    	    {
    	        ;
    	    }

    	    //Transmit Data to slave
    	    USCI_B_SPI_transmitData(USCI_B0_BASE, POT_COMMAND);

//    	    //USCI_A0 TX buffer ready?
//    	    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
//    	                                         USCI_B_SPI_TRANSMIT_INTERRUPT))
//    	    {
//    	        ;
//    	    }

    	    //Transmit Data to slave
    	    USCI_B_SPI_transmitData(USCI_B0_BASE, transmitData);
    	    set_SLAVE_HIGH(&DIGI_POT);

    	    __delay_cycles(10000);
    	    __delay_cycles(10000);
//    	    __delay_cycles(10000);

    	}

    	while(transmitData++ != high_value )
    	    	{
    		enable_SLAVE(&DIGI_POT);
    	    	    //USCI_A0 TX buffer ready?
    	    	    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
    	    	                                         USCI_B_SPI_TRANSMIT_INTERRUPT))
    	    	    {
    	    	        ;
    	    	    }

    	    	    //Transmit Data to slave
    	    	    USCI_B_SPI_transmitData(USCI_B0_BASE, POT_COMMAND);

    	    	    //USCI_A0 TX buffer ready?
//    	    	    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
//    	    	                                         USCI_B_SPI_TRANSMIT_INTERRUPT))
//    	    	    {
//    	    	        ;
//    	    	    }

    	    	    //Transmit Data to slave
    	    	    USCI_B_SPI_transmitData(USCI_B0_BASE, transmitData);
    	    	    set_SLAVE_HIGH(&DIGI_POT);

    	    	    __delay_cycles(10000);
    	    	    __delay_cycles(10000);
    	//    	    __delay_cycles(10000);

    	    	}
//    	transmitData = delay_value;
    }


    //CPU off, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
}





//******************************************************************************
//
//This is the USCI_B0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B0_VECTOR)))
#endif
void USCI_B0_ISR(void)
{
    switch(__even_in_range(UCB0IV,4))
    {
    //Vector 2 - RXIFG
    case 2:
        //USCI_A0 TX buffer ready?
        while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
                                             USCI_B_SPI_TRANSMIT_INTERRUPT))
        {
            ;
        }

        receiveData = USCI_B_SPI_receiveData(USCI_B0_BASE);

        //Increment data
        transmitData++;

        //Send next value
        USCI_B_SPI_transmitData(USCI_B0_BASE,
                                transmitData
                                );

        //Delay between transmissions for slave to process information
        __delay_cycles(40);

        break;
    default: break;
    }
}




#endif /* DRIVERLIB_TEST_SPI_H_ */