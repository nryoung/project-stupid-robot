/*******************************************************************************

    Microchip IrDA Standard Stack

Summary:
    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the OBEX protocol.

Description:
    IrDA_OBEX.h - IrDA Stack OBEX Protocol Definitions File

    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the OBEX protocol.  Stack
    users should include the IrDA Definitions header file irdep.h at the top of
    their application, along with the driver header for their selected protocol.

    Protocol                Header File
    -----------------------------------
    irCOMM 3-wire raw       IrDA_COMM.h
    irCOMM 9-wire cooked    IrDA_COMMX.h
    OBEX                    IrDA_OBEX.h

*******************************************************************************/
//DOM-IGNORE-BEGIN
/******************************************************************************

Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
KO                 11-Oct-2006  v1.0
KO                 21-Jun-2007  v1.01
KO                 31-Oct-2008  v1.02

********************************************************************************

Software License Agreement

Copyright © 2007 Microchip Technology Inc. and its licensors.
All rights reserved.

Microchip licenses to you the right to: (1) install Software on a single
computer and use the Software with Microchip 16-bit microcontrollers and 16-bit
digital signal controllers (“Microchip Product”); and (2) at your own
discretion and risk, use, modify, copy and distribute the device driver files
of the Software that are provided to you in Source Code; provided that such
Device Drivers are only used with Microchip Products and that no open source or
free software is incorporated into the Device Drivers without Microchip’s prior
written consent in each instance.

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
TECHNOLOGY, SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO
ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*******************************************************************************
*/

//------------------------------------------------------------------------------
// Header Files
//------------------------------------------------------------------------------

#include "irdep.h"

//DOM-IGNORE-END

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

// These constants are default sizes for the strings used to store OBEX file data objects

#define FILE_DESCRIPTION_SIZE   80  // Default file description string size.
#define FILE_NAME_SIZE          80  // Default file name string size.

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/****************************************************************************
  Function:
    WORD IrDA_InitServerOBEX( void )

  Summary:
    This function initializes the OBEX server (secondary stack).

  Description:
    This function initializes the OBEX server (secondary stack).

  Precondition:
    Hardware has been initialized

  Parameters:
    None

  Return Values:
    0 - Success
    1 - LAP link failed

  Remarks:
    None
  ***************************************************************************/

WORD IrDA_InitServerOBEX( void );

/****************************************************************************
  Function:
    BYTE IrDA_ReceiveOBEX( BYTE *fileDescription, BYTE *fileName,
            void *fptrUserStore, BYTE *dataArray, DWORD maxLength,
            DWORD *dataLength, WORD timeout )
  Summary:
    This function receives an OBEX "file" from another IrDA device.

  Description:
    This function receives an OBEX "file" from another IrDA device.
    If fptrUser is NULL, the received data will be stored to RAM and
    dataArraymust be valid.  If fptrUser is not NULL, the received
    data will be passed to that function for the user to store
    elsewhere (for example, to EEPROM), and dataArray may be NULL.

  Precondition:
    Hardware has been initialized

  Parameters:
    fileDescription - pointer to a text description of the "file"
    fileName - name of the "file" to transfer
    fptrUse - function pointer to a user-defined data store function
    dataArray - pointer to the characters to send
    timeout - number of milliseconds to wait at connection points

  Return Values:
    0 - success
    IRDA_ERROR_USER_EXIT - app terminated by the user
    IRDA_ERROR_LINK_TIMEOUT - link connect timeout
    IRDA_ERROR_TIMEOUT - obex connect timeout

  Remarks:
    User-defined storage routines should used the passed index for
    determining the position of the new byte received, and not try
    to keep a local copy.
  ***************************************************************************/

BYTE    IrDA_ReceiveOBEX( BYTE *fileDescription, BYTE *fileName, void *fptrUserStore, BYTE *dataArray, DWORD maxLength, DWORD *dataLength, WORD timeout );

/****************************************************************************
  Function:
    WORD IrDA_SendOBEX( BYTE *fileDescription, BYTE *fileName,
            void *fptrUserRead, BYTE *dataArray, DWORD dataLength )

  Summary:
    This function sends an OBEX "file" to another IrDA device.

  Description:
    This function sends an OBEX "file" to another IrDA device.  The
    function performs the following:
        * initialize system
        * initialize stack
        * install the device drivers
        * perform a Get_remote_sel to get the remote selector of the
                service to connect to
        * perform an OBEX connect to connect to the remote OBEX server.
        * perform an OBEX put to transfer a VCF file or a MEMO file to
                the OBEX server.
        * perform an OBEX disconnect.

  Precondition:
    Hardware has been initialized

  Parameters:
    fileDescription - pointer to a text description of the "file"
    fileName - name of the "file" to transfer
    dataArray - pointer to the characters to send
    dataLength - number of characters in dataArray to send

  Return Values:
    0 - file transferred successfully
    1 - obex make failed.
    2 - obex SAR TX failed.
    3 - wait for server response timeout
    4 - unknown server response

    1001 - LAP link initialization failed
    1002 - Get remote selector failed
    1003 - No buffers
    1004 - OBEX connect failed
    1005 - Connection timeout
    1008 - No buffers available at disconnect
    1013 - OBEX server connection failed

  Remarks:
    None
  ***************************************************************************/

WORD IrDA_SendOBEX( BYTE *fileDescription, BYTE *fileName, void *fptrUserRead, BYTE *dataArray, DWORD dataLength );

/****************************************************************************
  Function:
    void    IrDA_TerminateOBEX( void )

  Summary:
    This function terminates the IrDA stack functioning.

  Description:
    None

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void    IrDA_TerminateOBEX( void );

