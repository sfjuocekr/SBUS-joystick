A very simple SBUS USB HID joystick

on a Teensy 3.2:

Connect SBUS to RX1.
Connect power to 3V for 3.3v or if your transmitter needs 5v use VUSB near Micro-USB port on the back.
Connect ground.

Flash your Teensy using the Teensy Loader from https://www.pjrc.com/teensy/loader.html

or...

Compile and modify it yourself!


By default the channel map is as follows:

ROLL = channel 2
PITCH = channel 1
YAW = channel 4
THROTTLE = channel 3

AUX1 = channel 8
AUX2 = channel 7

SWA = channel 5
SWB = channel 6

AUX channels are analog

Switches use two buttons, one for each state. This makes it easier to bind them to functions in the simulator.

If someone wants a 3-point switch, I could add it.

=====

If you want to compile it yourself, you will need the SBUS library from: https://github.com/bolderflight/SBUS