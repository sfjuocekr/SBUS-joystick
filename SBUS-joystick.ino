/**
 * A very simple HID joystick using a Teensy and SBUS receiver on RX1
 * 
 * USB type = FlightSim Controls + Joystick (USB_FLIGHTSIM_JOYSTICK)
 * Change JOYSTICK_SIZE from 12 to 64 in: <Path to Arduino IDE>\hardware\teensy\avr\cores\teensy3\usb_desc.h
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
#include <TimerOne.h>
//#include <TimerThree.h>

SBUS sbus(Serial1);

uint16_t channels[16];
bool failSafe, lostFrame;


void setup()
{
  //Serial.begin(115200);
  sbus.begin();
  
  Joystick.useManualSend(true);
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(sentData);
  
  //Timer3.initialize(1000000);
  //Timer3.attachInterrupt(sentSerial);
}


void sentData()
{
  Joystick.send_now();
}


/*void sentSerial()
{
  for (uint8_t _i = 0; _i < sizeof(channels) / sizeof(uint16_t); _i++)
  {
    Serial.print(String(_i) + ": ");
    Serial.print(channels[_i]);
    
    if (_i < sizeof(channels) / sizeof(uint16_t) - 1)
      Serial.print(" ");
    else
      Serial.println();
  }
    
  Serial.print("Failsafe: ");
  Serial.print(failSafe);
  Serial.print("\tFrame lost: ");
  Serial.println(lostFrame);
}*/


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
    
    Joystick.button(7, map(channels[SWC - 1], STARTPOINT, ENDPOINT, 0, 2) == 0 ? 1 : 0); // SWB LOW = button 7
    Joystick.button(8, map(channels[SWC - 1], STARTPOINT, ENDPOINT, 0, 2) == 1 ? 1 : 0); // SWB MID = button 8
    Joystick.button(9, map(channels[SWC - 1], STARTPOINT, ENDPOINT, 0, 2) == 2 ? 1 : 0); // SWB HIGH = button 9
        
    Joystick.button(10, map(channels[SWD - 1], STARTPOINT, ENDPOINT, 0, 2) == 0 ? 1 : 0); // SWB LOW = button 10
    Joystick.button(11, map(channels[SWD - 1], STARTPOINT, ENDPOINT, 0, 2) == 1 ? 1 : 0); // SWB MID = button 11
    Joystick.button(12, map(channels[SWD - 1], STARTPOINT, ENDPOINT, 0, 2) == 2 ? 1 : 0); // SWB HIGH = button 12
  }
}
