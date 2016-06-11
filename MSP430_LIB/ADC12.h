/*
 * ADC12.h
 *
 *  Created on: May 30, 2016
 *      Author: Mario Osborn
 *      THIS IS ONLY AN EXAMPLE
 */

#ifndef DRIVERLIB_MSP430_LIB_ADC12_H_
#define DRIVERLIB_MSP430_LIB_ADC12_H_


#include <ISR_ADC12.h>
//******************************************************************************
//!
//!   ADC12_A_A - Sample A0 Input, AVcc Ref, LED ON if A0 > 0.5*AVcc
//!   MSP430F552x Demo
//!
//!   Description: A single sample is made on A0 with reference to AVcc.
//!   Software sets ADC12SC to start sample and conversion - ADC12SC
//!   automatically cleared at EOC. ADC12_A_A internal oscillator times sample (16x)
//!   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12_A_A
//!   conversion complete, ADC12_A_ISR will force exit from LPM0 in Mainloop on
//!   reti. If A0 > 0.5*AVcc, P1.0 set, else reset.
//!
//!                 MSP430F552x
//!             -----------------
//!         /|\|                 |
//!          | |                 |
//!          --|RST       P6.0/A0|<- Vin
//!            |             P1.0|--> LED
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC12_A_A peripheral
//! - GPIO Port peripheral
//! - A0
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - ADC12_A_VECTOR
//!
//******************************************************************************



void ADC12_INIT(void)
{
    //Stop Watchdog Timer
    WDT_A_hold(WDT_A_BASE);

    UART_init();

    //P6.0 ADC option select
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P6,
        GPIO_PIN0
        );

    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Initialize the ADC12_A_A Module
    /*
     * Base address of ADC12_A_A Module
     * Use internal ADC12_A_A bit as sample/hold signal to start conversion
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC12_A_init(ADC12_A_BASE,
                 ADC12_A_SAMPLEHOLDSOURCE_SC,
                 ADC12_A_CLOCKSOURCE_ADC12OSC,
                 ADC12_A_CLOCKDIVIDER_1);

    ADC12_A_enable(ADC12_A_BASE);

    /*
     * Base address of ADC12_A_A Module
     * For memory buffers 0-7 sample/hold for 64 clock cycles
     * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
     * Disable Multiple Sampling
     */
    ADC12_A_setupSamplingTimer(ADC12_A_BASE,
                               ADC12_A_CYCLEHOLD_64_CYCLES,
                               ADC12_A_CYCLEHOLD_4_CYCLES,
                               ADC12_A_MULTIPLESAMPLESDISABLE);

    //Configure Memory Buffer
    /*
     * Base address of the ADC12_A_A Module
     * Configure memory buffer 0
     * Map input A0 to memory buffer 0
     * Vref+ = AVcc
     * Vr- = AVss
     * Memory buffer 0 is not the end of a sequence
     */
    ADC12_A_configureMemoryParam param = {0};
    param.memoryBufferControlIndex = ADC12_A_MEMORY_0;
    param.inputSourceSelect = ADC12_A_INPUT_A0;
    param.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
    param.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE,&param);

    //Enable memory buffer 0 interrupt
    ADC12_A_clearInterrupt(ADC12_A_BASE,
                           ADC12IFG0);
    ADC12_A_enableInterrupt(ADC12_A_BASE,
                            ADC12IE0);

    while(1)
    {
        //Enable/Start sampling and conversion
        /*
         * Base address of ADC12_A_A Module
         * Start the conversion into memory buffer 0
         * Use the single-channel, single-conversion mode
         */
        ADC12_A_startConversion(ADC12_A_BASE,
                                ADC12_A_MEMORY_0,
                                ADC12_A_SINGLECHANNEL);




        //LPM0, ADC12_A_ISR will force exit
        __bis_SR_register(LPM0_bits + GIE);
        //for Debugger
//        __no_operation();

//        // format and send to uart
//    	sprintf( UART_buffer, "ADC Value: #%d\n\r", V_read );
//
//    	UARTSendArray(&UART_buffer, strlen(UART_buffer));
//
//    	int i_count;
//    	i_count = 25;
//    	while(i_count--)
//    	{
//            _delay_cycles(10000);
//            _delay_cycles(10000);
//            _delay_cycles(10000);
//    	}

    }
}





#endif /* DRIVERLIB_MSP430_LIB_ADC12_H_ */
