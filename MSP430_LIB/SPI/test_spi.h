///*
// * test_spi.h
// *
// *  Created on: Jun 5, 2016
// *      Author: Mario Osborn
// */
//
//#ifndef DRIVERLIB_TEST_SPI_H_
//#define DRIVERLIB_TEST_SPI_H_
//
//////#include "driverlib.h"
////#include <gpio.h>
////#include <usci_b_spi.h>
//////*****************************************************************************
//////
//////Specify desired frequency of SPI communication
//////
//////*****************************************************************************
////#define DEFAULT_SPI_CLOCK_SPEED                          500000
//////uint8_t transmitData = 0x00, receiveData = 0x00;
////uint8_t returnValue = 0x00;
////
////enum CS_ACTIVE_VALUE{
////	ACTIVE_LOW,
////	ACTIVE_HIGH
////};
////
////typedef struct SLAVE_SELECT_GPIO{
////	uint8_t PORT;
////	uint16_t PIN;
////	int SS_ACTIVE_VALUE;
////}SLAVE_SELECT_GPIO;
////
////// THIS MAY BE USED LATTER
////typedef struct TARGET_COMMANDS{
////	uint8_t WRITE;
////	uint8_t READ;
////	uint8_t SHUT_DOWN;
////}TARGET_COMMANDS;
////
////void set_SLAVE_HIGH(SLAVE_SELECT_GPIO *PARAM);
////void set_SLAVE_LOW(SLAVE_SELECT_GPIO *PARAM);
////void init_SLAVE(SLAVE_SELECT_GPIO *PARAM);
////void init_SS_GPIO(SLAVE_SELECT_GPIO *PARAM);
////void enable_SLAVE(SLAVE_SELECT_GPIO *PARAM);
////void disable_SLAVE(SLAVE_SELECT_GPIO *PARAM);
////void init_SPI_B0(void);
////
////void sent_tx(SLAVE_SELECT_GPIO *PARAM, uint8_t *tx_data);
////
////void init_SS_GPIO(SLAVE_SELECT_GPIO *PARAM)
////{
////    //Set P1.1 for slave reset
////    //Set P1.0 to output direction
////    GPIO_setAsOutputPin(
////        PARAM->PORT,
////        PARAM->PIN
////        );
////}
////
////
////void enable_SLAVE(SLAVE_SELECT_GPIO *PARAM)
////{
////
////	// IF SLAVE IS ACTIVE HIGH, BRING THE CHIP LOW - TO DISABLE
////	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_HIGH)
////	{
////		set_SLAVE_HIGH(PARAM);
////	}
////
////	// ELSE IF THE SLAVE IS ACTIVE LOW, BRING THE CHIP HIGH - TO DISABLE
////	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_LOW)
////	{
////		set_SLAVE_LOW(PARAM);
////	}
////	return;
////
////}
////
////void disable_SLAVE(SLAVE_SELECT_GPIO *PARAM)
////{
////	// IF SLAVE IS ACTIVE HIGH, BRING THE CHIP LOW - TO DISABLE
////	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_HIGH)
////	{
////		set_SLAVE_LOW(PARAM);
////	}
////
////	// ELSE IF THE SLAVE IS ACTIVE LOW, BRING THE CHIP HIGH - TO DISABLE
////	if(PARAM->SS_ACTIVE_VALUE == ACTIVE_LOW)
////	{
////		set_SLAVE_HIGH(PARAM);
////	}
////	return;
////
////}
////
////void set_SLAVE_HIGH(SLAVE_SELECT_GPIO *PARAM)
////{
////	//Set P1.1 for slave reset
////	    GPIO_setOutputHighOnPin(
////			PARAM->PORT,
////			PARAM->PIN
////	        );
////}
////
////void set_SLAVE_LOW(SLAVE_SELECT_GPIO *PARAM)
////{
////    //Now with SPI signals initialized, reset slave
////    GPIO_setOutputLowOnPin(
////        PARAM->PORT,
////        PARAM->PIN
////        );
////}
////
////void init_SPI_B0(void)
////{
////	//P3.0(UCB0SIMO), P3.1(UCB0SOMI) AND P3.2(UCB0CLK)	// P3.5,4,0 option select
////	    GPIO_setAsPeripheralModuleFunctionInputPin(
////	        GPIO_PORT_P3,
////	        GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN0
////	        );
////
////	    //Initialize Master
////	    USCI_B_SPI_initMasterParam param = {0};
////	    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
////	    param.clockSourceFrequency = UCS_getSMCLK();
////	    param.desiredSpiClock = DEFAULT_SPI_CLOCK_SPEED;
////	    param.msbFirst = USCI_B_SPI_MSB_FIRST;
////	    param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
////	    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
////	    returnValue = USCI_B_SPI_initMaster(USCI_B0_BASE, &param);
////
////	    if(STATUS_FAIL == returnValue)
////	    {
////	        return;
////	    }
////
////	    //Enable SPI module
////	    USCI_B_SPI_enable(USCI_B0_BASE);
////
////	    //Enable Receive interrupt
////	    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
////	    USCI_B_SPI_enableInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
////	    return;
////
////}
////
////
////void init_SLAVE(SLAVE_SELECT_GPIO *PARAM)
////{
////    // INITIALIZE GPIO
////	init_SS_GPIO(PARAM);
////
////	// RESET SLAVE SELECT
////	disable_SLAVE(PARAM);
////    enable_SLAVE(PARAM);
////
////    //Wait for slave to initialize
////    __delay_cycles(100);
////    return;
////
////    //CPU off, enable interrupts
//////    __bis_SR_register(LPM0_bits + GIE);
////}
////
////
////void sent_tx(SLAVE_SELECT_GPIO *PARAM, uint8_t *tx_data)
////{
////	uint8_t POT_COMMAND = 0x11;// B00010001;
////
////	// ENABLE SLAVE SELECT LINE
////	enable_SLAVE(PARAM);
////
////	//USCI_A0 TX buffer ready?
////	while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
////			USCI_B_SPI_TRANSMIT_INTERRUPT))
////	{
////		;
////	}
////
////	//Transmit Data to slave
////	USCI_B_SPI_transmitData(USCI_B0_BASE, POT_COMMAND);
////
////	//USCI_A0 TX buffer ready?
////	while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
////			USCI_B_SPI_TRANSMIT_INTERRUPT))
////	{
////		;
////	}
////
////	//Transmit Data to slave
////	USCI_B_SPI_transmitData(USCI_B0_BASE, tx_data);
////
////	disable_SLAVE(PARAM);
////}
//
//#endif /* DRIVERLIB_TEST_SPI_H_ */
