# There is a new CRSF-Joystick at: https://github.com/sfjuocekr/CRSF-joystick
This suports CrossFire and has SBUS fallback.

# A very simple SBUS USB HID joystick on a Teensy 3.2
Connect SBUS to RX1.
Connect power to 3V for 3.3v or if your receiver needs 5v use VUSB near Micro-USB port on the back.
Connect ground.

Flash your Teensy using the Teensy Loader from https://www.pjrc.com/teensy/loader.html

or...

Compile and modify it yourself, you will need the SBUS library from: https://github.com/bolderflight/SBUS
... and edit usb_desc.h to change JOYSTICK_SIZE from 12 to 64. 

By default the channel map is as follows:

PITCH = channel 1
ROLL = channel 2
THROTTLE = channel 3
YAW = channel 4

AUX1 = channel 5
AUX2 = channel 6

Channels 7-14 are used for buttons and support three point switches!

Switches use one button for each state as this makes it easier to bind them to functions in the simulator, using a 2-point switch makes no difference ;)
