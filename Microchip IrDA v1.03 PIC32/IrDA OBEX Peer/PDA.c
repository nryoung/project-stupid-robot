/*

Microchip IrDA Standard Stack - OBEX Peer Demo

PDA.c

This application demostrates the use of the Microchip IrDA Standard Stack
with the OBEX protocol in peer mode.  It is designed to run on an Explorer 16
Demonstration Board with an IrDA Standard PICtail Plus.

To monitor the operation of this demo, connect the Explorer 16's DB9 connector
to a PC's serial port, and use a terminal emulation program to monitor the
output.  Set the terminal emulation program to 57600-8-N-1.

The application is designed to mimic a simple PDA.  By default, the application
is in server mode, and will accept client transmissions, sending the received
data out the UARTx serial port for display on a terminal program.  If the user
presses the RD6 button on the demo board, the application will go into client
mode and try to transmit a vCard to a server.


Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
KO                 11-Oct-2006  First release

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
// Include Files
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


#define CONFIG          (CN_ON | CN_IDLE_CON)
#define PINS            (CN15_ENABLE)
#define PULLUPS         (CN15_PULLUP_ENABLE)
#define INTERRUPT       (CHANGE_INT_ON | CHANGE_INT_PRI_1)



//------------------------------------------------------------------------------
// Configuration
//------------------------------------------------------------------------------

// Uncomment USE_MY_READ to see how the stack can use an application defined
// function to obtain data to transmit.
//#define USE_MY_READ

// Uncomment USE_MY_STORE to see how the stack can use an application defined
// function to store received data.
//#define USE_MY_STORE

// Define the size of the buffer for holding received data.
#define DATA_ARRAY_SIZE     512

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

BYTE    dataArray[DATA_ARRAY_SIZE];     // We'll make this global so we can use
                                        // a callback for storing data.
BYTE    sendCard = 0;                   // Flag to transmit the vCard.

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
    WORD    i;

    for (i=0; i<size; i++)
    {
        *destination++ = vcf_info[startIndex+i];
    }
}
#endif

/*******************************************************************************
Function: void myDataStore( DWORD index, DWORD maxSize, BYTE ch )

Precondition: None

Overview:
    This optional function is called when the stack has received data for the
    application and needs the application to store it.  This function is purely
    for demonstration - the stack has the built-in capability of reading from
    RAM.  However, an application can replace this function with a more
    complicated algorithm, such as writing to external memory.

Input:
    index           - Index where to store the data byte
    maxSize         - The maximum number of data bytes that can be stored, as
                      specified when the user called IrDA_ReceiveOBEX()
    ch              - The byte to store

Output: None.

*******************************************************************************/
#ifdef USE_MY_STORE
void myDataStore( DWORD index, DWORD maxSize, BYTE ch )
{
    if (index < maxSize)
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
    DWORD   dataLength;
    BYTE    temp,fileName[FILE_NAME_SIZE];
    BYTE    fileDescription[FILE_DESCRIPTION_SIZE];
    DWORD   i;
    WORD    result;

    UARTxInit();

    _TRISD6 = 1;
    _RD6 = 0;
    mCNOpen(CONFIG, PINS, PULLUPS);
    temp = mPORTDRead();
    ConfigIntCN(INTERRUPT);

     SYSTEMConfigPerformance(GetSystemClock());
     INTEnableSystemMultiVectoredInt();

    UARTxPrintString( "\r\nOBEX PDA.\r\n" );
    while (1)
    {
        UARTxPutChar( '-' );

        if (sendCard)
        {
            sendCard = 0;

            UARTxPrintString( "\r\nSending vCard...\r\n" );

            #ifdef USE_MY_READ
                result = IrDA_SendOBEX( "Microchip", "PIC24.vcf", myDataRead, NULL, sizeof( vcf_info ) );
            #else
                result = IrDA_SendOBEX( "Microchip", "PIC24.vcf", NULL, vcf_info, sizeof( vcf_info ) );
            #endif

            if (result)
            {
                UARTxPutHex(result);
                UARTxPrintString( " Error sending.\r\n\r\n" );
            }
            else
            {
                UARTxPrintString( "vCard sent.\r\n\r\n" );
            }
        }

        UARTxPutChar( '|' );

        if (!IrDA_InitServerOBEX())
        {
            #ifdef USE_MY_STORE
                result = IrDA_ReceiveOBEX( fileDescription, fileName, myDataStore, NULL, DATA_ARRAY_SIZE, &dataLength, 1000 );
            #else
                result = IrDA_ReceiveOBEX( fileDescription, fileName, NULL, dataArray, DATA_ARRAY_SIZE, &dataLength, 1000 );
            #endif
            if (!result)
            {
                UARTxPrintString( "\r\nReceived:\r\n" );
                for (i=0; i<dataLength; i++)
                {
                    UARTxPutChar( dataArray[i] );
                }
                UARTxPrintString( "\r\n\r\n" );
            }

            IrDA_TerminateOBEX();
        }
    }
}

/*******************************************************************************
Function: void __attribute__((__interrupt__)) _CNInterrupt(void)

Precondition: None

Overview:
    This ISR is called when there is a change on one of the specified pins.
    Since we've only enabled notification on change of RD6, we can assume
    that's the pin that has changed, and use its status to set a flag to send
    the vCard.

Input: None

Output: None.

*******************************************************************************/

void __ISR(_CHANGE_NOTICE_VECTOR, ipl1) ChangeNotice_Handler(void)
{      

    BYTE temp;
   
    temp = mPORTDRead();

    sendCard = 1;

    mCNClearIntFlag();   // clear the interrupt flag
}

