/**
 * A very simple HID joystick using a Teensy and SBUS receiver on RX1
 * 
 * USB type = serial + keyboard + mouse + joystick
 * TODO: write a custom HID joystick header
 * 
 * Sjoer van der Ploeg, 2018
**/

// Channel mapping
#define ROLL 2
#define PITCH 1
#define YAW 4
#define THROTTLE 3
#define AUX1 8
#define AUX2 7
#define SWA 5
#define SWB 6

#include "SBUS.h"

SBUS sbus(Serial1);

uint16_t channels[16];
bool failSafe;
bool lostFrame;

void setup()
{
  sbus.begin();
  Joystick.useManualSend(true);
}

void loop()
{
  if(sbus.read(&channels[0], &failSafe, &lostFrame))
  {
      Joystick.X(map(channels[ROLL - 1], 240, 1807, 0, 1023));
      Joystick.Y(map(channels[PITCH - 1], 240, 1807, 0, 1024));      
      Joystick.Z(map(channels[THROTTLE - 1], 240, 1807, 0, 1024));
      Joystick.Zrotate(map(channels[YAW - 1], 240, 1807, 0, 1024));
      Joystick.sliderLeft(map(channels[AUX1 - 1], 240, 1807, 0, 1024));
      Joystick.sliderRight(map(channels[AUX2 - 1], 240, 1807, 0, 1024));
      
      Joystick.button(1, map(channels[SWA - 1], 240, 1807, 0, 1) == 0 ? 0 : 1); // SWA ON = button 1
      Joystick.button(2, map(channels[SWA - 1], 240, 1807, 0, 1) == 0 ? 1 : 0); // SWA OFF = button 2
      Joystick.button(3, map(channels[SWB - 1], 240, 1807, 0, 1) == 0 ? 0 : 1); // SWB ON = button 3
      Joystick.button(4, map(channels[SWB - 1], 240, 1807, 0, 1) == 0 ? 1 : 0); // SWB OFF = button 4
  
      Joystick.send_now();
  }
}

