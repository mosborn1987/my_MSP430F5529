/*
 * ISR_ADC12.h
 *
 *  Created on: May 30, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_MSP430_LIB_ISR_ADC12_H_
#define DRIVERLIB_MSP430_LIB_ISR_ADC12_H_
uint16_t V_read = 0x00;
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC12_VECTOR)))
#endif
void ADC12_A_ISR(void)
{
    switch(__even_in_range(ADC12IV,34))
    {
    case  0: break;       //Vector  0:  No interrupt
    case  2: break;       //Vector  2:  ADC overflow
    case  4: break;       //Vector  4:  ADC timing overflow
    case  6:              //Vector  6:  ADC12IFG0
        //Is Memory Buffer 0 = A0 > 0.5AVcc?
    	V_read = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_0);
        if( V_read >= 450)
        {
            //set P1.0
            GPIO_setOutputHighOnPin(
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        }
        else
        {
            //Clear P1.0 LED off
            GPIO_setOutputLowOnPin(
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        }



        //Exit active CPU
        _BIC_SR(LPM0_EXIT);
//        __bic_SR_register_on_exit(LPM0_bits);
    case  8: break;       //Vector  8:  ADC12IFG1
    case 10: break;       //Vector 10:  ADC12IFG2
    case 12: break;       //Vector 12:  ADC12IFG3
    case 14: break;       //Vector 14:  ADC12IFG4
    case 16: break;       //Vector 16:  ADC12IFG5
    case 18: break;       //Vector 18:  ADC12IFG6
    case 20: break;       //Vector 20:  ADC12IFG7
    case 22: break;       //Vector 22:  ADC12IFG8
    case 24: break;       //Vector 24:  ADC12IFG9
    case 26: break;       //Vector 26:  ADC12IFG10
    case 28: break;       //Vector 28:  ADC12IFG11
    case 30: break;       //Vector 30:  ADC12IFG12
    case 32: break;       //Vector 32:  ADC12IFG13
    case 34: break;       //Vector 34:  ADC12IFG14
    default: break;
    }
}





#endif /* DRIVERLIB_MSP430_LIB_ISR_ADC12_H_ */
