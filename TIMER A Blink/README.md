# Read Me
## TIMER A Blink

This code toggles two LEDs on and off at separate rates based on two timer interrupts.  The rate is controlled by an input into an outside function created to convert the desired Hz into an input CCR value for the timers.

The code first includes its necessary header file along with a hzconvert.h file that has the function to convert the desired Hz into a CCR input.  The watchdog timer is turned off to stop the code from unnecessarily looping. Timer A1 and A0 are set to SMCLK with a divider of 8 and in up mode.  Both of their CCR interrupts are enabled.  The CCR values for both are added by plugging them the function found in the hzconvert.h header.  The function divides the Hz of the clock used by the divider and multiplying it by the inverse of the wanted Hz of the timer.  The LED pins are then set up appropriately and the processor is set to LPM0 when interrupted.  Timer interrupt statements are then set to their appropriate timers where they XOR the LEDs to toggle them on and off.
