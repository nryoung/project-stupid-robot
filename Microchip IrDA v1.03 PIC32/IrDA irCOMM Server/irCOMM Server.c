/*

Microchip IrDA Standard Stack - irCOMM 3-wire Raw Server Demo

irCOMM Server.c

This demo program shows how to use the irCOMM 3-wire raw protocol in server
mode.

This program will wait for a connection with a client.  When established, it
will read data from the client until the client disconnects.  The received data
will be sent to a terminal window via UART2.  To terminate the program early,
send a character from the terminal window.  Two different types of reads can
be demonstrated, either a single step read that locks the application, or a
multiple step read that allows the read to be performed in the background.

This program is designed to work with the IrDA irCOMM Client Demo.  Follow
the instructions below to utilize both demos together:

1. Program the irCOMM Server program into one Explorer 16 Demo Board with an
IrDA PICtail Plus.  Connect the Explorer 16's DB9 connector to a PC's serial
port, and use a terminal emulation program to monitor the output.  Set the
terminal emulation program to 57600-8-N-1.

2. Program the irCOMM Client program into a second Explorer 16 Demo Board with
an IrDA PICtail Plus.  If a second PC serial port is available, connect the
Explorer 16's DB9 connector to a PC's serial port, and use a terminal emulation
program to monitor the output.  Set the terminal emulation program to
57600-8-N-1.

3. Allow the irCOMM Server to execute.  A banner should appear on the server's
PC terminal program.

4. Align the irCOMM Server and irCOMM Client infrared transceivers, and allow
the irCOMM Client to execute.  If the irCOMM Client is connected to a terminal
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
#include <IrDA\IrDA_COMM.h>
#include <plib.h>
// Include the header file for displaying information on a terminal
// program using UART2.
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

// To perform the read operation with a single function call that locks the
// system for the duration of the read, uncomment USE_SINGLE_STEP_READ.  To
// perform the read in the background, comment the definition out.

#define USE_SINGLE_STEP_READ

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

#define MAX_SIZE    64              // Read buffer size


//******************************************************************************
//******************************************************************************
//******************************************************************************

int main( void )
{
    WORD    dataLength;
    BYTE    inData[MAX_SIZE];
    BYTE    result;

    SYSTEMConfigPerformance(GetSystemClock());
    INTEnableSystemMultiVectoredInt();

    UARTxInit();
    UARTxPrintString( "\r\nirCOMM 3-wire Raw Server Demo\r\n\r\n" );

    result = IrDA_CommInit();
    if (result)
    {
        UARTxPutHex( result );
        UARTxPrintString( " Error initializing the stack.\r\n" );
    }

    if (!result)
    {
        UARTxPrintString( "Waiting for client...\r\n" );
       
        while (1)
        {
            result = IrDA_OpenCommServer(3000);
            if (result)
            {
                if (UARTxIsPressed())
                {
                    UARTxGetChar();
                    goto Finished;
                }
            }
            else
            {
                break;
            }
        }

        UARTxPrintString( "Receiving...\r\n" );

        #ifdef USE_SINGLE_STEP_READ

            while ((result = IrDA_ReadComm( inData, MAX_SIZE, 0, &dataLength )) != 0x01)
            {
                if (!result)
                {
                    int i;

                    for (i = 0; i<dataLength; i++)
                    {
                        UARTxPutChar( inData[i] );
                    }
                    UARTxPrintString( "\r\n" );
                }
            }

        #else

            while (!IrDA_CommBackground())
            {
                result = IrDA_ReadResultComm( &dataLength );
                switch( result )
                {
                    case IRDA_COMM_READ_COMPLETE:
                        if (dataLength)
                        {
                            int i;

                            for (i = 0; i<dataLength; i++)
                            {
                                UARTxPutChar( inData[i] );
                            }
                            UARTxPrintString( "\r\n" );
                        }
                        IrDA_ReadResetComm();
                        break;

                    case IRDA_COMM_READ_NOT_IN_PROGRESS:
                        result = IrDA_ReadInitComm( inData, MAX_SIZE, 0 ); //5000 );
                        if (result)
                        {
                            UARTxPrintString( "Disconnected at Read\r\n" );
                        }
                        break;

                    case IRDA_COMM_READ_NOT_COMPLETE:
                        break;
                }
            }
        #endif

        result = IrDA_CloseCommServer( 2000 );
        if (result)
        {
            UARTxPutHex( result );
            UARTxPrintString( " Error closing the server.\r\n" );
        }
        UARTxPrintString( "Disconnected\r\n" );
    }

Finished:

    result = IrDA_CommTerminate();
    if (result)
    {
        UARTxPutHex( result );
        UARTxPrintString( " Error terminating the stack.\r\n" );
    }

    UARTxPrintString( "Demonstration complete!\r\n" );

    while (1);
}
