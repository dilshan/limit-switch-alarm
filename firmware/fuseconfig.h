/* 
 * File:   fuseconfig.h
 * Project: A simple alarm controller for limit switch or flow switches.
 * Author: Dilshan R Jayakody [jayakody2000lk@gmail.com]
 * 
 * https://github.com/dilshan/limit-switch-alarm
 *
 * Created on October 6, 2024, 12:47 PM
 */

#ifndef FUSECONFIG_H
#define	FUSECONFIG_H

#define _XTAL_FREQ 4000000

// PIC12F508 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config OSC = IntRC      // Oscillator Selection bits (internal RC oscillator)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection off)
#pragma config MCLRE = ON       // GP3/MCLR Pin Function Select bit (GP3/MCLR pin function is MCLR)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#endif	/* FUSECONFIG_H */

