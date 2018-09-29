 /**Michael Maloney
 * 9/28/2018
 * timerblink.c
 * 2 LED blinks based on interrupts
 */
 
#include <msp430.h>
#include <hzconvert.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  TA0CTL = TASSEL_2 + MC_1 + ID_3; //Timer A0 = smclock, up count mode, divider of 8
  TA1CTL = TASSEL_2 + MC_1 + ID_3; //Timer A1 = ^
  TA0CCTL0 = CCIE; // CCR0 interrupt enabled
  TA1CCTL0 = CCIE; // CCR0 interrupt enabled

  TA1CCR0 = timerConvert(3, 8); // 3hz //CCRs set to value given by other timerConvert function
  TA0CCR0 = timerConvert(7, 8); // 7hz

  P1DIR |= BIT0;        //P1.0 and P4.7 set to output
  P4DIR |= BIT7;

  _BIS_SR(CPUOFF + GIE);          // Enter LPM0 when interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0;                          // Toggle P1.0
}
// Timer A1 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1 (void)
{
   P4OUT ^= BIT7;                      // Toggle P4.7
}
