///*
// * USCI_B0_SPI.h
// *
// *  Created on: Jun 5, 2016
// *      Author: Mario Osborn
// */
//
//#ifndef DRIVERLIB_MSP430_LIB_USCI_B0_SPI_H_
//#define DRIVERLIB_MSP430_LIB_USCI_B0_SPI_H_
//
//#include <stdint.h>
//#include <ISR_USCI_B0.h>
////#include <stdbool.h>
//
//#include "driverlib.h"
//
////*****************************************************************************
////
////Specify desired frequency of SPI communication
////
////*****************************************************************************
//#define default_SPI_CLOCK_SPEED                          500000
//
////// VARIABLES
////uint8_t transmitData, receiveData, returnValue = 0x00;
//
//enum CS_ACTIVE_VALUE{
//	ACTIVE_LOW,
//	ACTIVE_HIGH
//};
//
//typedef struct SLAVE_SELECT{
//	uint8_t PORT;
//	uint16_t PIN;
//	int SS_ACTIVE_VALUE;
//}SLAVE_SELECT;
//
//
//// INIT FUNCTION
//void SPI_B0_channel_init(void);
//
//// sub_INIT FUNCTIONS
//void SPI_B0_slect_pins(void);
//void SPI_B0_init_MASTER(void);
//void SPI_B0_enable_SPI(void);
//void SPI_B0_enable_rx_interrupt(void);
//
//
//// micro_FUNCTIONS
//void SPI_B0_init_slave(SLAVE_SELECT *SLAVE);
//void SPI_B0_reset_slave(uint8_t m_PORT, uint16_t m_PIN, int m_SS_VALUE);
//void SPI_B0_disable_slave(uint8_t m_PORT, uint16_t m_PIN, int m_SS_VALUE);
//void SPI_B0_enable_slave(uint8_t m_PORT, uint16_t m_PINS, int m_SS_VALUE);
//void SPI_B0_bring_slave_HIGH(uint8_t m_PORT, uint16_t m_PIN);
//void SPI_B0_bring_slave_LOW(uint8_t m_PORT, uint16_t m_PIN);
//
//
//// TRANSMIT RECIEVE FUNCTIONS
//void SPI_B0_tx_byte(SLAVE_SELECT *SLAVE, uint8_t *tx_byte);
//
//
//// INIT FUNCTION
//void SPI_B0_channel_init(void)
//{
//	// SELECT THE PERIPHERAL PINS
//	SPI_B0_slect_pins();
//
//	// INITIALIZE MASTER
//	SPI_B0_init_MASTER();
//
//	// ENABLE SPI
//	SPI_B0_enable_SPI();
//
//	// ENABLE THE RECIEVER INTERRUPT
//	SPI_B0_enable_rx_interrupt();
//
//
//	// RESET SLAVE
//
//	return;
//
//
//}
//
//// sub_INIT FUNCTIONS
//void SPI_B0_slect_pins(void)
//{
//    //P3.0(UCB0SIMO), P3.1(UCB0SOMI) AND P3.2(UCB0CLK)
//    GPIO_setAsPeripheralModuleFunctionInputPin(
//        GPIO_PORT_P3,
//		GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
//        );
//
//    return;
//
//}
//
//// initialize the master spi b0 channel
//void SPI_B0_init_MASTER(void)
//{
//    //Initialize Master
//    USCI_B_SPI_initMasterParam param = {
//    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK,
//    param.clockSourceFrequency = UCS_getSMCLK(),
//    param.desiredSpiClock = default_SPI_CLOCK_SPEED,
//    param.msbFirst = USCI_B_SPI_MSB_FIRST,
//    param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
//    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,
//    returnValue = USCI_B_SPI_initMaster(USCI_B0_BASE, &param)};
//
//    if(STATUS_FAIL == returnValue)
//    {
//        return;
//    }
//
//    return;
//
//}
//
//// enable spi BASE B0
//void SPI_B0_enable_SPI(void)
//{
//	//Enable SPI module
//	USCI_B_SPI_enable(USCI_B0_BASE);
//	return;
//}
//
//void SPI_B0_enable_rx_interrupt(void)
//{
//    //Enable Receive interrupt
//    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
//    USCI_B_SPI_enableInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
//    return;
//
//}
//
//
//
//
//
//
//// TRANSMIT RECIEVE FUNCTIONS
//void SPI_B0_tx_byte(SLAVE_SELECT *SLAVE, uint8_t *tx_byte)
//{
//	// enable pin - THIS IS DEPENDENT ON THE SS DEFINITION(ACTIVE LOW/HIGH)
//	SPI_B0_enable_slave(SLAVE->PORT, SLAVE->PIN, SLAVE->SS_ACTIVE_VALUE);
//
//	//USCI_A0 TX buffer ready?
//	while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_TRANSMIT_INTERRUPT))
//	{
//		;
//	}
//
//    //Transmit Data to slave
//    USCI_B_SPI_transmitData(USCI_B0_BASE, tx_byte);
//
//	SPI_B0_disable_slave(SLAVE->PORT, SLAVE->PIN, SLAVE->SS_ACTIVE_VALUE);
//
//	return;
//
//}
//
//void SPI_B0_init_slave(SLAVE_SELECT *SLAVE)
//{
//	// SET SLAVE SELECT PIN - AS OUTPUT
//	GPIO_setAsOutputPin(SLAVE->PORT, SLAVE->PIN);
//	SPI_B0_reset_slave(SLAVE->PORT, SLAVE->PIN, SLAVE->SS_ACTIVE_VALUE);
//	return;
//
//}
//
//void SPI_B0_reset_slave(uint8_t m_port, uint16_t m_pin, int m_SS_VALUE)
//{
//	SPI_B0_disable_slave(m_port, m_pin, m_SS_VALUE);
//	__delay_cycles(100);
//	SPI_B0_enable_slave(m_port, m_pin, m_SS_VALUE);
//
//	//Wait for slave to initialize
//	__delay_cycles(100);
//	return;
//}
//
//
//
//void SPI_B0_disable_slave(uint8_t m_PORT, uint16_t m_PIN, int m_SS_VALUE)
//{
//	// IF SLAVE IS ACTIVE HIGH, BRING THE CHIP LOW - TO DISABLE
//	if(m_SS_VALUE == ACTIVE_HIGH)
//	{
//		SPI_B0_bring_slave_LOW(m_PORT, m_PIN);
//	}
//
//	// ELSE IF THE SLAVE IS ACTIVE LOW, BRING THE CHIP HIGH - TO DISABLE
//	if(m_SS_VALUE == ACTIVE_LOW)
//	{
//		SPI_B0_bring_slave_HIGH(m_PORT, m_PIN);
//	}
//	return;
//
//}
//
//void SPI_B0_enable_slave(uint8_t m_PORT, uint16_t m_PIN, int m_SS_VALUE)
//{
//	// IF SLAVE IS ACTIVE HIGH, BRING CHIP HIGH - TO ENABLE CHIP
//	if(m_SS_VALUE == ACTIVE_HIGH)
//	{
//		SPI_B0_bring_slave_HIGH(m_PORT, m_PIN);
//	}
//
//	// ELSE IF SLAVE IS ACTIVE LOW, BRING CHIP LOW - TO ENABLE CHIP
//	if(m_SS_VALUE == ACTIVE_LOW)
//	{
//		SPI_B0_bring_slave_LOW(m_PORT, m_PIN);
//	}
//	return;
//}
//
//void SPI_B0_bring_slave_HIGH(uint8_t m_PORT, uint16_t m_PIN)
//{
//	//Set P1.1 for slave reset
//	GPIO_setOutputHighOnPin(
//			m_PORT,
//			m_PIN
//			);
//	return;
//}
//
//void SPI_B0_bring_slave_LOW(uint8_t m_PORT, uint16_t m_PIN)
//{
//    //Now with SPI signals initialized, reset slave
//    GPIO_setOutputLowOnPin(
//			m_PORT,
//			m_PIN
//			);
//    return;
//}
//
//
//
//#endif /* DRIVERLIB_MSP430_LIB_USCI_B0_SPI_H_ */
