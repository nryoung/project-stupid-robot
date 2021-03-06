/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright � 2007 Microchip Technology Inc. and its licensors.  All              
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

// Created by the Microchip IrDA Stack Tool, Version 1.3.3.0, 11/29/2010, 15:45:51

// Created for use with library IrDA_PIC32_OP.a

#include <IrDA\irdep.h>
#include "IrDA_def.h"

UBYTE connect_params[] =
{                       
    0x01,0x02,SUPPORTED_BAUD_RATES,SUPPORTED_BAUD_RATES_HIGH,
    0x82,0x01,MAX_TTT,              
    0x83,0x01,FRAME_SIZE,           
    0x84,0x01,WINDOW_SIZE,          
    0x85,0x01,ADDITIONAL_BOF,       
    0x86,0x01,MIN_TURN_AROUND_TIME, 
    0x08,0x01,LINK_DISCONNECT_TIME  
};                                  

UBYTE device_info[] =               
{                                   
    #if EXTENSION_BIT >=1           
        HINT_BYTE_0,HINT_BYTE_1,    
    #else                           
        HINT_BYTE_0,                
    #endif                          
    0x00,                           
    DEVICE_NAME_BYTES               
};                                  

UBYTE myDeviceName[] = DEVICE_NAME_STRING;

UBYTE *GetDeviceInfoAndSize(UINT *size) 
{                                       
    *size = sizeof(device_info);        
    return device_info;                 
}                                       

UBYTE *GetConnectParamsAndSize(UINT *size) 
{                                          
    *size = sizeof(connect_params);        
    return connect_params;                 
}                                          

