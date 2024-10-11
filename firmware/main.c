/*
 * File:   main.c
 * Project: A simple alarm controller for limit switch or flow switches.
 * Author: Dilshan R Jayakody [jayakody2000lk@gmail.com]
 * 
 * https://github.com/dilshan/limit-switch-alarm
 *
 * Created on October 6, 2024, 12:46 PM
 * 
 * MIT License
 * 
 * Copyright (c) 2024 Dilshan R Jayakody
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "fuseconfig.h"
#include <xc.h>

#define ALARM_RUNNING   0x01
#define ALARM_MUTE      0x02
#define BUZZER_PLUSE    0x04
#define BUZZER_CONTINUE 0x08

#define BASE_TIMER_LIMIT  900   // Closer to 10 second (adjusted by considering the code execution delays).
#define MUTE_TIMEOUT_LIMIT  30  // Closer to 5 minutes. (MUTE_TIMEOUT_LIMIT * 10 * BASE_TIMER_LIMIT)/(60 * 1000)

#define RING_CONTINUE_LIMIT 20

// Buzzer on and off delay limits.
#define RING_OFF_LIMIT  750
#define RING_ON_LIMIT   250

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
        if((++baseTimer) >= BASE_TIMER_LIMIT)
        {
          // base time delay has been reached (10 seconds in default configuration)!
          baseTimer = 0; 
          
          if((++timeout) >= MUTE_TIMEOUT_LIMIT)
          {
            // mute timeout delay has been reached!
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
        if(((controllerState & BUZZER_PLUSE) == 0x00) && ((++pulseTimer) >= RING_OFF_LIMIT))
        {
          // Turn off buzzer (15sec in default configuration)!
          GPIO = GPIO & 0xEF;   
          pulseTimer = 0;
          controllerState = controllerState | BUZZER_PLUSE;
        }
        
        if((controllerState & BUZZER_PLUSE) && ((++pulseTimer) >= RING_ON_LIMIT))
        {
          
          // Turn on buzzer (5sec in default configuration)!
          GPIO = GPIO | 0x10;
          pulseTimer = 0;
          controllerState = controllerState & (~BUZZER_PLUSE);
          buzzerCount++;
        } 

        // After defined beep cycles, buzzer starts to ring continuously...
        if(buzzerCount > RING_CONTINUE_LIMIT)
        {
          GPIO = GPIO | 0x10;
          controllerState = controllerState | BUZZER_CONTINUE;
        }
      }
      
      __delay_ms(10);
  }
  
  return;
}
