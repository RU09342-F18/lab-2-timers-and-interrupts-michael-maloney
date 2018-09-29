# Read Me
## Button Based Delay

This code is intended to start an LED at a blinking speed of 10Hz.  When a button is pressed a counter is then started, increasing 100 times a second to have the precision of the counter in the 1/100s of a second.  Once the counter button is released, the LED will then blink with the period length as long as the button hold.

The hzconvert.h header file is also included in this file to to help with wanted Hz conversions.  The initial Timer A0 is set to the ACLK with a divider of 8 in up mode with flags enabled.  The initial CCR for this timer is set to 10Hz through use of the timerConvert function.  All necessary pins are set to in or out depending on whether they are to be LEDs or the button.  The button is then set as an interrupt flag on the high-to-low edge.  LPM0 is then set every time an interrupt happens.

When the button is pressed Timer A1 turns on with a cycling speed of 100Hz.  Every time it cycles, the timer flag sets off another interrupt where a counter increments by one.  As long as the button is pressed, this will continue to happen.  The counter value will be converted to a usable number for the CCR of Timer A0.  Once the button is unpressed, an if statement runs and Timer A1 stops running, the counter stops incrementing, and the button interrupt flag is set off.  This allows the Timer A0 interrupt to continually run based on the newly set CCR from the counter.  This A0 interrupt flashes the LED on with a 50% duty cycle and a period as long as the button is held.
