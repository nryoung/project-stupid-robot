/*

Microchip IrDA Standard Stack - OBEX Client Demo

OBEX Client.c

This application demostrates the use of the Microchip IrDA Standard Stack
with the OBEX protocol in client mode.  It is designed to run on an Explorer 16
Demonstration Board with an IrDA Standard PICtail Plus.

The application is designed to interact with a second Explorer 16 Demonstration
Board programmed with the OBEX Server Demo or with an OBEX enabled device such
as a PDA.

To monitor the operation of this demo, connect the Explorer 16's DB9 connector
to a PC's serial port, and use a terminal emulation program to monitor the
output.  Set the terminal emulation program to 57600-8-N-1.

On power up, this application will try to connect to an OBEX server and send
it a vCard.


Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
KO                 11-Oct-2006  v1.0

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

//------------------------------------------------------------------------------
// Header Files
//------------------------------------------------------------------------------

// Include the Microchip generic typedefs
#include "GenericTypeDefs.h"

// Include the header file for IrDA support.
#include <IrDA\IrDA_OBEX.h>
#include <plib.h>
// Include the header file for displaying information on a terminal
// program using UARTx.
#include "uart.h"

// Include the header file for the selected device
#include "HardwareProfile.h" //DEVICE_HEADER_FILE

//------------------------------------------------------------------------------
// Configuration Bits
//------------------------------------------------------------------------------

//_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF & ~0x0200 )
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI )

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
//#include "PIC32Config.h"
//------------------------------------------------------------------------------
// Configuration
//------------------------------------------------------------------------------

// Uncomment USE_MY_READ to see how the stack can use an application defined
// function to obtain data to transmit.
//#define USE_MY_READ

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

BYTE vcf_info[] =
{
    "BEGIN:VCARD\r\n" \
    "N:Microcontroller;PIC32MX\r\n" \
    "ADR;DOM;WORK:;;2355 W. Chandler Blvd.;Chandler;AZ;85224;USA\r\n" \
    "ORG:Microchip Technology, Inc.\r\n" \
    "TITLE:32-bit Microcontroller\r\n" \
    "TEL;PREF;WORK;VOICE:(480) 792-7200\r\n" \
    "URL;WORK:www.microchip.com/PIC32\r\n" \
    "BDAY:20060418\r\n" \
    "END:VCARD\r\n"
};


/*******************************************************************************
Function: void myDataRead( BYTE *destination, DWORD startIndex, WORD size )

Precondition: None

Overview:
    This optional function obtains the specified number of bytes from the
    specified start index and places them in the specified destination.  This
    function is purely for demonstration - the stack has the built-in capability
    of reading from RAM.  However, an application can replace this function
    with a more complicated algorithm, such as reading from external memory.

Input:
    *destination    - Pointer to the location in RAM where the data needs to
                      be stored
    startIndex      - Index of the first data byte needed
    size            - Number of data bytes needed

Output: None.

*******************************************************************************/
#ifdef USE_MY_READ
void myDataRead( BYTE *destination, DWORD startIndex, WORD size )
{
    WORD  i;

    for (i=0; i<size; i++)
    {
        *destination++ = vcf_info[startIndex+i];
    }
}
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main( void )
{
    WORD    result;

    SYSTEMConfigPerformance(GetSystemClock());
    INTEnableSystemMultiVectoredInt();

    UARTxInit();

    UARTxPrintString( "\r\nOBEX Client.\r\n" );

    UARTxPrintString( "Sending vCard...\r\n" );

    #ifdef USE_MY_READ
        result = IrDA_SendOBEX( "Microchip", "PIC24.vcf", myDataRead, NULL, sizeof( vcf_info ) );
    #else
        result = IrDA_SendOBEX( "Microchip", "PIC24.vcf", NULL, vcf_info, sizeof( vcf_info ) );
    #endif

    if (result)
    {
        UARTxPutHex(result);
        UARTxPrintString( " Error sending.\r\n" );
    }
    else
    {
        UARTxPrintString( "vCard sent.\r\n\r\n" );
    }

    while (1);
}
