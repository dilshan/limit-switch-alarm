/*
 * File:   main.c
 * Project: A simple alarm controller for limit switch or flow switches.
 * Author: Dilshan R Jayakody [jayakody2000lk@gmail.com]
 * 
 * https://github.com/dilshan/limit-switch-alarm
 *
 * Created on October 6, 2024, 12:46 PM
 */

#include "fuseconfig.h"
#include <xc.h>

#define ALARM_RUNNING   0x01
#define ALARM_MUTE      0x02
#define BUZZER_PLUSE    0x04
#define BUZZER_CONTINUE 0x08

void main(void)
{
  // Enable weak pull-ups on GP0 and GP1.
  OPTION = 0x40;
  
  // Configure GPIO
  // GP0 - [IN]  - Limit switch input.
  // GP1 - [IN]  - Mute switch input.
  // GP4 - [OUT] - Buzzer control relay.
  TRISGPIO = 0x03;
  GPIO = 0x03;
  
  unsigned char controllerState = 0x00;
  unsigned char timeout = 0, buzzerCount = 0;
  unsigned short baseTimer = 0, pulseTimer = 0;
  
  while(1)
  {
      // Check limit switch is triggered.
      if((GPIO & 0x01) == 0x00)
      {
        if((controllerState & ALARM_RUNNING) == 0x00)
        {
          // New trigger has been detected!
          controllerState = controllerState | ALARM_RUNNING;
          
          // Turn on relay output.
          GPIO = GPIO | 0x10;
        }
      }
      else
      {
        // Limit switch is in open position.
        if(controllerState & ALARM_RUNNING)
        {
          // Just now the limit switch has been released! (and reset everything!)
          controllerState = 0;
          buzzerCount = 0;
          timeout = 0;
          pulseTimer = 0;
          baseTimer = 0;
          
          // Turn off relay output.
          GPIO = GPIO & 0xEF;
        }
      }
      
      // Check mute switch is pressed by the user.
      if((GPIO & 0x02) == 0x00)
      {
        // Check limit switch is still in limit.
        if(controllerState & ALARM_RUNNING)
        {
          controllerState = controllerState | ALARM_MUTE;  
          timeout = 0;
          
          // Turn off relay output.
          GPIO = GPIO & 0xEF;
        }
      }
      
      // Timeout counter.
      if(controllerState & ALARM_MUTE)
      {
        if((++baseTimer) >= 900)
        {
          // 10sec delay has been reached!
          baseTimer = 0; 
          
          if((++timeout) >= 30)
          {
            //5min timeout delay has been reached!
            timeout = 0;
            
            controllerState = controllerState & (~ALARM_MUTE);
          }
        }
      }
      
      // Handle buzzer delays in continues operation...
      if((controllerState & ALARM_RUNNING) && ((controllerState & ALARM_MUTE) == 0x00) 
                                           && ((controllerState & BUZZER_CONTINUE) == 0x00))
      {
        // Alarm is running and to avoid buzzer heat-ups, lets pulse the output.
        if(((controllerState & BUZZER_PLUSE) == 0x00) && ((++pulseTimer) >= 750))
        {
          // Turn off buzzer after 15sec ring!
          GPIO = GPIO & 0xEF;   
          pulseTimer = 0;
          controllerState = controllerState | BUZZER_PLUSE;
        }
        
        if((controllerState & BUZZER_PLUSE) && ((++pulseTimer) >= 250))
        {
          
          // Turn on buzzer after 5sec delay!
          GPIO = GPIO | 0x10;
          pulseTimer = 0;
          controllerState = controllerState & (~BUZZER_PLUSE);
          buzzerCount++;
        } 

        // After 20 beep cycles, buzzer starts to ring continuously...
        if(buzzerCount > 20)
        {
          GPIO = GPIO | 0x10;
          controllerState = controllerState | BUZZER_CONTINUE;
        }
      }
      
      __delay_ms(10);
  }
  
  return;
}
