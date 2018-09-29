/**Michael Maloney
 * 9/28/2018
 * fr5529delay.c
 * LED blinks based on length of press
 */

#include <msp430.h>
#include <hzconvert.h>

volatile int counter; //counter of how long button is press in seconds, polled 100 times/sec

void main(void) //initializing
{

  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  TB0CTL = TBSSEL_1 + MC_1 + ID_3; //Timer B0 = smclock, up count mode, divider of 8
  TB0CCTL0 = CCIE; // CCR0 interrupt enabled
  TB0CCR0 = timerConvert(10, 8);

  P1DIR |= BIT0;            // P1.0 set to out
  P2DIR &= ~BIT0;           // P2.0 set to out

  P1REN &= BIT1;                    // Resistor enabled for button
  P1OUT &= BIT1;                    // Resistor changed to pull-up
  P1IE |= BIT1;                    // P1.1 interrupt enabled
  P1IES |= BIT1;                  // P1.1 Hi/lo edge
  P1IFG &= ~BIT1;                // Initial flag set off

  _BIS_SR(CPUOFF + GIE);          // Enter LPM0 when interrupt
}


// Timer A0 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Timer_A (void)
{
   TB1CTL = TBSSEL_1 + MC_1 + ID_3;    // Timer B1 ACLK/8, up
   TB1CCTL0 = CCIE;                    // Enable flags
   TB1CCR0 = timerConvert(100, 8);     // 100 flags/sec

   int CCRcount = 32000/8 * counter/100;    //CCRcount is rounded int value of the Hz/8 * time
   if (CCRcount > 0xffff) {CCRcount = 0xfffe;}  //if overflow, set CCRcount to 1 below max
   TB0CCR0 = CCRcount;                      //CCR of Timer A0 set to CCRcount

   if((P1IN & BIT1) == BIT1){           // If P1.1 is unpressed,
       P1IFG &= 0x00;                   // Interrupt closes
       counter = 0;                     // Counter = 0;
   }
}

// Timer B1 interrupt service routine
#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer_B1 (void)
{
    counter++;      // Counter increments every 1/100th second
    P2OUT |= BIT0;  // P2.0 set on to show button is pressed (mostly for debugging)
}

// Timer B0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B0 (void)
{
   TB1CTL &= ~MC_3;   // Timer A1 set off
   P1OUT ^= BIT0;     // LED blinks
   P2OUT &= ~BIT0;    // P2.0 turns off
}
