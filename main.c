#include <msp430.h>

int main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P4SEL = BIT5+BIT4; // P3.4,5 = USCI_A0 TXD/RXD
UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
UCA1CTL1 |= UCSSEL_2; // SMCLK
UCA1BR0 = 6; // 1MHz 9600 (see User's Guide)
UCA1BR1 = 0; // 1MHz 9600
UCA1MCTL = UCBRS_0 + UCBRF_13 + UCOS16; // Modln UCBRSx=0, UCBRFx=0,
// over sampling
UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
UCA1IE |= UCRXIE; // Enable USCI_A0 RX interrupt

__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
__no_operation(); // For debugger
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
switch(__even_in_range(UCA1IV,4))
{
case 0:break; // Vector 0 - no interrupt
case 2: // Vector 2 - RXIFG
while (!(UCA1IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
UCA1TXBUF = UCA1RXBUF; // TX -> RXed character
break;
case 4:break; // Vector 4 - TXIFG
default: break;
}
}
