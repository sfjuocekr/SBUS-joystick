A very simple SBUS USB HID joystick on a Teensy 3.2:

Connect SBUS to RX1.
Connect power to 3V for 3.3v or if your transmitter needs 5v use VUSB near Micro-USB port on the back.
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

SWA = channel 7 (3-point) 
SWB = channel 8 (3-point) 
SWC = channel 9 (3-point) 
SWD = channel 10 (3-point) 

Switches use one button for each state as this makes it easier to bind them to functions in the simulator, using a 2-point switch makes no difference ;)


usb_desc.h:

#elif defined(USB_JOYSTICK)
  #define VENDOR_ID		0x16C0
  #define PRODUCT_ID		0x0488
  #define BCD_DEVICE		0x0211
  #define MANUFACTURER_NAME	{'U','G','H'}
  #define MANUFACTURER_NAME_LEN	3
  #define PRODUCT_NAME		{'K','w','a','d',' ','S','i','m',' ','J','o','y','s','t','i','c','k'}
  #define PRODUCT_NAME_LEN	17
  #define EP0_SIZE		64
  #define NUM_ENDPOINTS         3
  #define NUM_USB_BUFFERS	20
  #define NUM_INTERFACE		2
  #define SEREMU_INTERFACE      0	// Serial emulation
  #define SEREMU_TX_ENDPOINT    1
  #define SEREMU_TX_SIZE        64
  #define SEREMU_TX_INTERVAL    1
  #define SEREMU_RX_ENDPOINT    2
  #define SEREMU_RX_SIZE        32
  #define SEREMU_RX_INTERVAL    2
  #define JOYSTICK_INTERFACE    1	// Joystick
  #define JOYSTICK_ENDPOINT     3
  #define JOYSTICK_SIZE         64	//  12 = normal, 64 = extreme joystick
  #define JOYSTICK_INTERVAL     1
  #define ENDPOINT1_CONFIG	ENDPOINT_TRANSMIT_ONLY
  #define ENDPOINT2_CONFIG	ENDPOINT_RECEIVE_ONLY
  #define ENDPOINT3_CONFIG	ENDPOINT_TRANSMIT_ONLY


boards.txt:

teensy31.menu.usb.joystick=Joystick
teensy31.menu.usb.joystick.build.usbtype=USB_JOYSTICK
teensy31.menu.usb.joystick.fake_serial=teensy_gateway

