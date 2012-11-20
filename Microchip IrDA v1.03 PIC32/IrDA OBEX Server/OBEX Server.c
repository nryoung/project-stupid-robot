/*

Microchip IrDA Standard Stack - OBEX Server Demo

OBEX Server.c

This application demostrates the use of the Microchip IrDA Standard Stack
with the OBEX protocol in server mode.  It is designed to run on an Explorer 16
Demonstration Board with an IrDA Standard PICtail Plus.

The application is designed to interact with a second Explorer 16 Demonstration
Board programmed with the OBEX Client Demo or with an OBEX enabled device such
as a PDA.

To monitor the operation of this demo, connect the Explorer 16's DB9 connector
to a PC's serial port, and use a terminal emulation program to monitor the
output.  Set the terminal emulation program to 57600-8-N-1.

This application will repeatedly wait for a client to establish a connection
with it and send it a vCard.  If the read operation times out, a small indicator
will be sent to the terminal emulation window, and the application will try
again.  If a client does send a vCard, the vCard contents will be displayed on
the terminal emulation window.


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


//------------------------------------------------------------------------------
// Configuration
//------------------------------------------------------------------------------

// Uncomment USE_MY_STORE to see how the stack can use an application defined
// function to store received data.
//#define USE_MY_STORE

// Define the size of the buffer for holding received data.
#define DATA_ARRAY_SIZE     512

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

BYTE    dataArray[DATA_ARRAY_SIZE];

/*******************************************************************************
Function: void myDataStore( DWORD index, DWORD maxLength, BYTE ch )

Precondition: None

Overview:
    This optional function is called when the stack has received data for the
    application and needs the application to store it.  This function is purely
    for demonstration - the stack has the built-in capability of reading from
    RAM.  However, an application can replace this function with a more
    complicated algorithm, such as writing to external memory.

Input:
    index           - Index where to store the data byte
    maxLength       - The maximum number of data bytes that can be stored, as
                      specified when the user called IrDA_ReceiveOBEX()
    ch              - The byte to store

Output: None.

*******************************************************************************/
#ifdef USE_MY_STORE
void myDataStore( DWORD index, DWORD maxLength, BYTE ch )
{
    if (index < maxLength)
    {
        dataArray[index] = ch;
    }
}
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main( void )
{
    DWORD   dataLength = 0;
    BYTE    fileName[FILE_NAME_SIZE];
    BYTE    fileDescription[FILE_DESCRIPTION_SIZE];
    DWORD   i;
    BYTE    result = 0xFF;

    UARTxInit();
    UARTxPrintString( "\r\nOBEX Server.\r\n" );

     SYSTEMConfigPerformance(GetSystemClock());
     INTEnableSystemMultiVectoredInt();

    if (!IrDA_InitServerOBEX())
    {
        UARTxPrintString( "Receiving... " );

        while (1)
        {
            #ifdef USE_MY_STORE
                result = IrDA_ReceiveOBEX( fileDescription, fileName, myDataStore, NULL, DATA_ARRAY_SIZE, &dataLength, 2000 );
            #else
                result = IrDA_ReceiveOBEX( fileDescription, fileName, NULL, dataArray, DATA_ARRAY_SIZE, &dataLength, 4000 );
            #endif

            if (result)
            {
                UARTxPutChar('-');
            }
            else
            {
                UARTxPrintString( "\r\n" );
                for (i=0; i<dataLength; i++)
                {
                    UARTxPutChar( dataArray[i] );
                }
                UARTxPrintString( "\r\n" );
            }
        }
    }
    else
    {
        UARTxPrintString( "Error initializing server.\r\n" );
    }

    IrDA_TerminateOBEX();

    while(1);
}

