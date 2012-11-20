/*

HardwareProfile.h

This file sets up certain system-specific parameters used to configure UART2 for
operation.  Some of these parameters, like the target device and clock speed,
are already set up in IrDA_def.h.  Therefore, we will include that file and
use those values.

Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Anton Alkhimenok    10/21/05    ...
KO                 12-Oct-2006  v1.0
KO                 31-Oct-2008  v1.2, changed from system.h to HardwareProfile.h

********************************************************************************

Software License Agreement

Microchip Technology Inc. ("Microchip") licenses to you the right to use, copy,
modify and distribute the software - including source code - only for use with
Microchip microcontrollers or Microchip digital signal controllers; provided
that no open source or free software is incorporated into the Source Code
without Microchip’s prior written consent in each instance.

The software is owned by Microchip and its licensors, and is protected under
applicable copyright laws.  All rights reserved.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING
BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

********************************************************************************
*/

#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//******************************************************************************
// Include Files
//******************************************************************************

#include "IrDA_def.h"
#if defined(__PIC24F__)
    #include <p24Fxxxx.h>
#elif defined(__PIC24H__)
    #include <p24Hxxxx.h>
#elif defined(__dsPIC30F__)
    #include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
    #include <p33Fxxxx.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>    
#else
    #error Unsupported processor
#endif

//******************************************************************************
// Constants
//******************************************************************************

// External oscillator frequency (we'll use the value in IrDA_dep.h)
#define GetSystemClock()            SYSTEM_CLOCK
#ifdef __PIC32MX__
  #define   GetPeripheralClock()        PERIPHERAL_CLOCK 
#else
  #define GetPeripheralClock()        (GetSystemClock())
#endif
#define GetInstructionClock()       (GetSystemClock())

/* define UART for debug output 
Cannot use same UART for Debug and IrDA Communication  */
#define USE_DEBUG_UART2   

#if defined(USE_DEBUG_UART1)
   #if defined (USE_UART1)
       #error Cannot use UART1 both for Debug and IrDA Communicaiton
   #endif
#elif defined(USE_DEBUG_UART2)
   #if defined (USE_UART2)
       #error Cannot use UART2 both for Debug and IrDA Communicaiton
   #endif
#elif defined(USE_DEBUG_UART3)
   #if defined (USE_UART3)
       #error Cannot use UART3 both for Debug and IrDA Communicaiton
   #endif
#else
    #Warning No UART enabled for Debug!
#endif

// Define the baud rate constants
#define BAUDRATE2       57600
#define BRG_DIV2        4
#define BRGH2           1

#endif
