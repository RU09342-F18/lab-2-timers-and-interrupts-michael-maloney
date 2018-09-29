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

  TA1CCR0 = timerConvert(10, 8); //CCRs set to value given by other timerConvert function
  TA0CCR0 = timerConvert(5, 8);


  P1OUT &= 0x00;               //Clears outputs
  P1DIR &= 0x00;                //All pins set to out
  P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 set to input
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
   P1OUT ^= BIT6;                      // Toggle P1.6
}



////// Header and .C Files pasted below //////



////  hzconvert.h

int timerConvert(int Hz, int div);



////  hzconvert.c

#include <hzconvert.h>

int timerConvert(int Hz,  int div){
   int CCR = 0;
   CCR= 1000000/div * Hz;
   return CCR;
}

