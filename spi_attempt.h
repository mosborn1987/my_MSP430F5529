//#include "driverlib.h"
//#include <USCI_B0_SPI.h>
//
////*****************************************************************************
////! This example shows how SPI master talks to SPI slave using 3-wire mode.
////! Incrementing data is sent by the master starting at 0x01. Received data is
////! expected to be same as the previous transmission.  USCI RX ISR is used to
////! handle communication with the CPU, normally in LPM0. If high, P1.0 indicates
////! valid data reception.  Because all execution after LPM0 is in ISRs,
////! initialization waits for DCO to stabilize against ACLK.
////! ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
////!
////! Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
////! slave reset signal conflicts with slave's JTAG; to work around, use IAR's
////! "Release JTAG on Go" on slave device.  If breakpoints are set in
////! slave RX ISR, master must stopped also to avoid overrunning slave
////! RXBUF.
////!
////!                  MSP430F5438A
////!                 -----------------
////!            /|\ |                 |
////!             |  |                 |
////!    Master---+->|RST              |
////!                |                 |
////!                |             P3.1|-> Data Out (UCB0SIMO)
////!                |                 |
////!                |             P3.2|<- Data In (UCB0SOMI)
////!                |                 |
////!                |             P3.3|-> Serial Clock Out (UCB0CLK)
////!
////!
////! This example uses the following peripherals and I/O signals.  You must
////! review these and change as needed for your own board:
////! - SPI peripheral
////! - GPIO Port peripheral (for SPI pins)
////! - UCB0SIMO
////! - UCB0SOMI
////! - UCB0CLK
////!
////! This example uses the following interrupt handlers.  To use this example
////! in your own application you must add these interrupt handlers to your
////! vector table.
////! - USCI_A0_VECTOR
////!
////*****************************************************************************
//
////*****************************************************************************
////
////Specify desired frequency of SPI communication
////
////*****************************************************************************
//
//
//
//void main(void)
//{
//    //Stop watchdog timer
//    WDT_A_hold(WDT_A_BASE);
//
//    // INITIALIZE DIGIPOT - SLAVE SELECT
//    SLAVE_SELECT DIGI_POT = {
//    		DIGI_POT.PORT = 0x01, //GPIO_PORT_P1,
//			DIGI_POT.PIN = 0X40,//0x40, //GPIO_PIN6,
//    		DIGI_POT.SS_ACTIVE_VALUE = ACTIVE_LOW
//    };
//
//
//    // INITIALIZE DIGI POT
//    SPI_B0_init_slave(&DIGI_POT);
//
//
//    // INITIALIZE SPI CH B0
//    SPI_B0_channel_init();
//
//
//    //Initialize data values
//    uint8_t low_value = 0x10;
//    uint8_t high_value = 0x7F;
//    transmitData = high_value;
//    uint8_t POT_COMMAND = 0x11;// B00010001; write to pot
//    while(1)
//    {
//    	//  Write to pot command
//		SPI_B0_tx_byte(&DIGI_POT, &POT_COMMAND);
//
//		// Write value to pot
//		SPI_B0_tx_byte(&DIGI_POT, &high_value);
//
//    	//  Write to pot command
//		SPI_B0_tx_byte(&DIGI_POT, &POT_COMMAND);
//
//		// Write value to pot
//		SPI_B0_tx_byte(&DIGI_POT, &low_value);
//
//
////    	while(transmitData--!=low_value)
////    	{
////    		//  Write to pot command
////    		SPI_B0_tx_byte(&DIGI_POT, POT_COMMAND);
////
////    		// Write value to pot
////    		SPI_B0_tx_byte(&DIGI_POT, transmitData);
////
////    	    __delay_cycles(10000);
////    	    __delay_cycles(10000);
////
////    	}
////
////    	while(transmitData++ != high_value )
////    	{
////    		//  Write to pot command
////    		SPI_B0_tx_byte(&DIGI_POT ,POT_COMMAND);
////
////    		// Write value to pot
////    		SPI_B0_tx_byte(&DIGI_POT ,POT_COMMAND);
////
////    	    __delay_cycles(10000);
////    	    __delay_cycles(10000);
////    	}
//    }
//
//
//    //CPU off, enable interrupts
//    __bis_SR_register(LPM0_bits + GIE);
//}
//
