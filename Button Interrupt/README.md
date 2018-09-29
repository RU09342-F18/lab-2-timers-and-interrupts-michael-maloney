# Read Me
## Button Interrupt

This code is designed to turn an LED on and off by press of a button.  This utilizes a port interrupt instead of a loop, saving power.

The code first turns off the watchdog timer and sets all necessary pins on to either input or output, depending on what pin is to be the flashing LED and what pins is the button input.  A pull-up resistor is then programmed onto the button.  Next, an interrupt is attached to the button bin where it only triggers on the high-to-low edge of a button press.  The flag is then set to off.  A port interrupt is then added that triggers when the button is pushed, toggling the LED pin and turning the flag off once it is toggled.  
