/*

Microchip IrDA Standard Stack - irCOMM 9-wire Cooked Client Demo

irCOMMX Client.c

This demo program shows how to use the irCOMM 9-wire cooked protocol in client
mode.

This program will attempt to establish a connection with a server.  If
successful, it will send a test string multiple times to the server.  The
constant TEST_STRING_TRANSMISSIONS defines the number of times that the string
is sent to the server.

This program is designed to work with the IrDA irCOMMX Server Demo.  Follow
the instructions below to utilize both demos together:

1. Program the irCOMMX Server program into one Explorer 16 Demo Board with an
IrDA PICtail Plus.  Connect the Explorer 16's DB9 connector to a PC's serial
port, and use a terminal emulation program to monitor the output.  Set the
terminal emulation program to 57600-8-N-1.

2. Program the irCOMMX Client program into a second Explorer 16 Demo Board with
an IrDA PICtail Plus.  If a second PC serial port is available, connect the
Explorer 16's DB9 connector to a PC's serial port, and use a terminal emulation
program to monitor the output.  Set the terminal emulation program to
57600-8-N-1.

3. Allow the irCOMMX Server to execute.  A banner should appear on the server's
PC terminal program.

4. Align the irCOMMX Server and irCOMMX Client infrared transceivers, and allow
the irCOMMX Client to execute.  If the irCOMMX Client is connected to a terminal
emulation program, it will display a banner, and indicate what internal
processing is taking place.

5. If data transmission is successful, the test string(s) will be displayed on
the server's terminal emulation program.  If errors occur, they will be
displayed on the terminal emulation program.

6.  The demos are designed for a single communication session.  To repeat the
demonstration, or to try again in case of errors, halt both applications and
return to step 3.


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
#include <IrDA\IrDA_COMMX.h>
#include <plib.h>
// Include the header file for displaying information on a terminal
// program using UART.
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
// Constants
//------------------------------------------------------------------------------

#define TEST_STRING_TRANSMISSIONS       5

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main( void )
{
    BYTE    j;
    BYTE    myData[] = "This is a test string!";
    BYTE    result;

    SYSTEMConfigPerformance(GetSystemClock());
    INTEnableSystemMultiVectoredInt();

    UARTxInit();
    UARTxPrintString( "\r\nirCOMM 9-wire Cooked Client Demo\r\n\r\n" );

    result = IrDA_CommXInit();
    if (result)
    {
        UARTxPutHex( result );
        UARTxPrintString( " Error initializing the stack.\r\n" );
    }

    result = IrDA_OpenCommXClient();
    if (result)
    {
        UARTxPutHex( result );
        UARTxPrintString( " Cannot establish communications with the server.\r\n" );
    }
    else
    {
        for (j=0; j<TEST_STRING_TRANSMISSIONS; j++)
        {
            if (!(result = IrDA_InitCommXDataPacket()))
            {
                if (!(result = IrDA_NoControlParameters()))
                {
                    UARTxPrintString( "Sending the test string...\r\n" );
                    result = IrDA_WriteCommX( myData, sizeof(myData)-1 );
                    if (result)
                    {
                        UARTxPutHex( result );
                        UARTxPrintString( " Error writing the test string.\r\n" );
                    }
                }
                else
                {
                    UARTxPutHex( result );
                    UARTxPrintString( " Error initializing the control parameters.\r\n" );
                }
            }
            else
            {
                UARTxPutHex( result );
                UARTxPrintString( " Error initializing the data packet.\r\n" );
            }
        }
        result = IrDA_CloseCommXClient( 3000 );
        if (result)
        {
            UARTxPutHex( result );
            UARTxPrintString( " Error closing the client.\r\n" );
        }
    }

    result = IrDA_CommXTerminate();
    if (result)
    {
        UARTxPutHex( result );
        UARTxPrintString( " Error terminating the stack.\r\n" );
    }

    UARTxPrintString( "Demonstration complete!\r\n" );

    while (1);
}

