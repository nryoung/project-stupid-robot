/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright © 2007 Microchip Technology Inc. and its licensors.  All              
rights reserved.                                                                
                                                                                
Microchip licenses to you the right to: (1) install Software on a single        
computer and use the Software with Microchip 16-bit microcontrollers and        
16-bit digital signal controllers ("Microchip Product"); and (2) at your        
own discretion and risk, use, modify, copy and distribute the device            
driver files of the Software that are provided to you in Source Code;           
provided that such Device Drivers are only used with Microchip Products         
and that no open source or free software is incorporated into the Device        
Drivers without Microchip's prior written consent in each instance.             
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY         
KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY              
WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A          
PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE             
LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,               
CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY           
DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY         
INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR         
LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,                 
SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY         
DEFENSE THEREOF), OR OTHER SIMILAR COSTS.                                       
                                                                                
********************************************************************************
*/

// Created by the Microchip IrDA Stack Tool, Version 1.3.3.0, 11/29/2010, 15:43:06

// Created for use with library IrDA_PIC32_OC.a

#ifndef __IRDA_DEF_
#define __IRDA_DEF_

#define DEVICE_NAME_STRING "Microchip"
#define DEVICE_NAME_BYTES 'M','i','c','r','o','c','h','i','p',0x00

#define IRDA_PROTOCOL_IRLPT             0
#define IRDA_PROTOCOL_IRCOMM3WIRERAW    1
#define IRDA_PROTOCOL_IRCOMM3WIRECOOKED 2
#define IRDA_PROTOCOL_IRCOMM9WIRECOOKED 3
#define IRDA_PROTOCOL_OBEX              4

#define IRDA_PROTOCOL_TYPE IRDA_PROTOCOL_OBEX
#define IRDA_MODE_TYPE PRIMARY
#define SUPPORTED_BAUD_RATES 0x02
#define SUPPORTED_BAUD_RATES_HIGH 0x00
#define MAX_TTT 0x01
#define FRAME_SIZE 0x01
#define WINDOW_SIZE 0x01
#define ADDITIONAL_BOF 0x80
#define MIN_TURN_AROUND_TIME 0x01
#define LINK_DISCONNECT_TIME 0x03
#define EXTENSION_BIT 0x80
#define HINT_BYTE_0 0x90
#define HINT_BYTE_1 0x20

// Values calculated for an oscillator frequency of 80000000 Hz

#define SYSTEM_CLOCK 80000000UL
#define PERIPHERAL_CLOCK 80000000UL

#define MILLISECONDS_PER_TICK 10  // -0.000% error
#define TIMER_PRESCALER TIMER_PRESCALER_16
#define TIMER_PERIOD 50000

#define USE_UART1

// These are the Baud Rate Generator (UxBRG) and High Baud Rate Select (BRGH)
// values to generate the indicated baud rates at the indicated clock
// frequency.  Review device errata to determine if any adjustments are required.

#define BAUDRATE_9600 519  // -0.2% error
#define BRGH_9600 0
#define BAUDRATE_19200 259  // -0.2% error
#define BRGH_19200 0
#define BAUDRATE_38400 129  // -0.2% error
#define BRGH_38400 0
#define BAUDRATE_57600 85  // -0.9% error
#define BRGH_57600 0
#define BAUDRATE_115200 42  // -0.9% error
#define BRGH_115200 0

#endif

