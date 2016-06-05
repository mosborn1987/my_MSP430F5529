///*
// * ISR_USCI_B0.h
// *
// *  Created on: Jun 5, 2016
// *      Author: Mario Osborn
// */
//
//#ifndef DRIVERLIB_MSP430_LIB_ISR_USCI_B0_H_
//#define DRIVERLIB_MSP430_LIB_ISR_USCI_B0_H_
//
////#include <USCI_B0_SPI.h>
//// VARIABLES
//uint8_t transmitData, receiveData, returnValue = 0x00;
//
////******************************************************************************
////
////This is the USCI_B0 interrupt vector service routine.
////
////******************************************************************************
//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=USCI_B0_VECTOR
//__interrupt
//#elif defined(__GNUC__)
//__attribute__((interrupt(USCI_B0_VECTOR)))
//#endif
//void USCI_B0_ISR(void)
//{
//    switch(__even_in_range(UCB0IV,4))
//    {
//    //Vector 2 - RXIFG
//    case 2:
//        //USCI_A0 TX buffer ready?
//        while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
//                                             USCI_B_SPI_TRANSMIT_INTERRUPT))
//        {
//            ;
//        }
//
//        receiveData = USCI_B_SPI_receiveData(USCI_B0_BASE);
//
//        //Increment data
//        transmitData++;
//
//        //Send next value
//        USCI_B_SPI_transmitData(USCI_B0_BASE,
//                                transmitData
//                                );
//
//        //Delay between transmissions for slave to process information
//        __delay_cycles(40);
//
//        break;
//    default: break;
//    }
//}
//
//
//
//#endif /* DRIVERLIB_MSP430_LIB_ISR_USCI_B0_H_ */
