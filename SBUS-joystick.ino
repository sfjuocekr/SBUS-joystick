/**
 * A very simple HID joystick using a Teensy and SBUS receiver on RX1
 * 
 * USB type = serial + keyboard + mouse + joystick
 * TODO: write a custom HID joystick header
 * 
 * Sjoer van der Ploeg, 2018
**/

// SBUS range
#define STARTPOINT 240
#define ENDPOINT 1807

// Channel mapping
#define PITCH 1
#define ROLL 2
#define THROTTLE 3
#define YAW 4
#define AUX1 5
#define AUX2 6
#define SWA 7
#define SWB 8
#define SWC 9
#define SWD 10

#include "SBUS.h"

SBUS sbus(Serial1);

uint16_t channels[16];
bool failSafe, lostFrame;

void setup()
{
  sbus.begin();
  Joystick.useManualSend(true);
}

void loop()
{
  if(sbus.read(&channels[0], &failSafe, &lostFrame))
  {
      Joystick.X(map(channels[ROLL - 1], STARTPOINT, ENDPOINT, 0, 65535));
      Joystick.Y(map(channels[PITCH - 1], STARTPOINT, ENDPOINT, 0, 65535));      
      Joystick.Z(map(channels[THROTTLE - 1], STARTPOINT, ENDPOINT, 0, 65535));
      
      Joystick.Zrotate(map(channels[YAW - 1], STARTPOINT, ENDPOINT, 0, 65535));
      Joystick.Xrotate(map(channels[AUX1 - 1], STARTPOINT, ENDPOINT, 0, 65535));
      Joystick.Yrotate(map(channels[AUX2 - 1], STARTPOINT, ENDPOINT, 0, 65535));
      
      Joystick.button(1, map(channels[SWA - 1], STARTPOINT, ENDPOINT, 0, 2) == 0 ? 1 : 0); // SWA LOW = button 1
      Joystick.button(2, map(channels[SWA - 1], STARTPOINT, ENDPOINT, 0, 2) == 1 ? 1 : 0); // SWA MID = button 2
      Joystick.button(3, map(channels[SWA - 1], STARTPOINT, ENDPOINT, 0, 2) == 2 ? 1 : 0); // SWA HIGH = button 3
      
      Joystick.button(4, map(channels[SWB - 1], STARTPOINT, ENDPOINT, 0, 2) == 0 ? 1 : 0); // SWB LOW = button 4
      Joystick.button(5, map(channels[SWB - 1], STARTPOINT, ENDPOINT, 0, 2) == 1 ? 1 : 0); // SWB MID = button 5
      Joystick.button(6, map(channels[SWB - 1], STARTPOINT, ENDPOINT, 0, 2) == 2 ? 1 : 0); // SWB HIGH = button 6
      
      Joystick.button(7, map(channels[SWC - 1], STARTPOINT, ENDPOINT, 0, 1) == 0 ? 1 : 0); // SWC LOW = button 7
      Joystick.button(8, map(channels[SWC - 1], STARTPOINT, ENDPOINT, 0, 1) == 1 ? 1 : 0); // SWC HIGH = button 8
      
      Joystick.button(9, map(channels[SWD - 1], STARTPOINT, ENDPOINT, 0, 1) == 0 ? 1 : 0); // SWD LOW = button 9
      Joystick.button(10, map(channels[SWD - 1], STARTPOINT, ENDPOINT, 0, 1) == 1 ? 1 : 0); // SWD HIGH = button 10
      
      Joystick.send_now();
  }
}

