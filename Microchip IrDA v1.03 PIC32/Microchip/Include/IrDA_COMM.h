/*******************************************************************************

    Microchip IrDA Standard Stack

Summary:
    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the irCOMM 3-wire raw
    protocol.

Description:
    IrDA_COMM.h - IrDA Stack irCOMM 3-wire Raw Protocol Definitions File

    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the irCOMM 3-wire raw
    protocol.  Stack users should include the IrDA Definitions header file irdep.h
    at the top of their application, along with the driver header for their
    selected protocol.

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

********************************************************************************
*/

//------------------------------------------------------------------------------
// Header Files
//------------------------------------------------------------------------------

#include "irdep.h"

//DOM-IGNORE-END

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

// Copied from COMM.h for application use

#define COMM_THREE_WIRE_RAW                 20  // Used by IrDA_OpenCommClient to determine exact protocol.
#define COMM_LPT                            21  // Used by IrDA_OpenCommClient to determine exact protocol.
#define COMM_DEFAULT                        21  // Used by IrDA_OpenCommClient to determine exact protocol.


#define IRDA_COMM_READ_COMPLETE             0   // Return code for IrDA_ReadResultComm.
#define IRDA_COMM_READ_NOT_IN_PROGRESS      1   // Return code for IrDA_ReadResultComm.
#define IRDA_COMM_READ_NOT_COMPLETE         2   // Return code for IrDA_ReadResultComm.

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/****************************************************************************
  Function:
    BYTE IrDA_CommBackground( void )

  Summary:
    This function processes events as long as the device is connected.

  Description:
    This function processes events as long as the device is connected.
    It also monitors any timeouts that must be checked.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - device is still connected
    1 - device no longer connected

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_CommBackground( void );

/****************************************************************************
  Function:
    BYTE IrDA_CommInit( void )

  Summary:
    This function initializes the stack.

  Description:
    This function initializes the stack.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success
    1 - failure

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_CommInit( void );

/****************************************************************************
  Function:
    BYTE IrDA_CommTerminate( void )

  Summary:
    This function terminates the stack, turning off the clock and
    the UART.

  Description:
    This function terminates the stack, turning off the clock and
    the UART.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success

  Remarks:
    After this function is called, IrDA_CommInit must be called
    again to restart the stack.
  ***************************************************************************/
BYTE IrDA_CommTerminate( void );

//DOM-IGNORE-BEGIN
#define Irda_CommTerminate IrDA_CommTerminate
//DOM-IGNORE-END

/****************************************************************************
  Function:
    BYTE IrDA_OpenCommClient( BYTE type )

  Summary:
    This function tries to establish a client IrDA connection with
    another device.

  Description:
    This function tries to establish a client IrDA connection with
    another device.

  Precondition:
    IrDA_CommInit has been called and returned with success.

  Parameters:
    type - COMM_LPT or COMM_THREE_WIRE_RAW

  Return Values:
    0x00 - success
    0x41 - no buffers
    0x42 - bad comm state

  Remarks:
    This is the place where the connection type makes a difference.
    This determines what class name we ask for.
  ***************************************************************************/

#if ((PRISEC == PRIMARY) || (PRISEC == PEER))
    BYTE IrDA_OpenCommClient( BYTE type );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_CloseCommClient( WORD timeout )

  Summary:
    This function disconnects from the IrDA COMM server.

  Description:
    This function disconnects from the IrDA COMM server.

  Precondition:
    IrDA_OpenCommClient has been called and returned with success.

  Parameters:
    timeout - time to wait for frames to clear and a link disconnect

  Return Values:
    0x00 - success
    0x04 - failure

  Remarks:
    After this function is called, IrDA_OpenCommClient can be called without
    having to call IrDA_CommInit.
  ***************************************************************************/

#if ((PRISEC == PRIMARY) || (PRISEC == PEER))
    BYTE IrDA_CloseCommClient( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_OpenCommServer( WORD timeout )

  Summary:
    This function tries to establish a server IrDA connection with
    another device.

  Description:
    This function tries to establish a server IrDA connection with
    another device.

  Precondition:
    IrDA_CommInit has been called and returned with success.

  Parameters:
    timeout - 0-65535ms to wait for a connection

  Return Values:
    0 - Success
    1 - Link connect failed
    2 - Application connection failed

  Remarks:
    None
  ***************************************************************************/

#if ((PRISEC == SECONDARY) || (PRISEC == PEER))
    BYTE IrDA_OpenCommServer( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_CloseCommServer( WORD timeout )

  Summary:
    This function disconnects from the IrDA COMM client.

  Description:
    This function disconnects from the IrDA COMM client.

  Precondition:
    IrDA_OpenCommServer has been called and returned with success.

  Parameters:
    timeout - time to wait for frames to clear

  Return Values:
    0x00 - success
    0x04 - failure

  Remarks:
    After this function is called, IrDA_OpenCommServer can be called
    without having to call IrDA_CommInit.
  ***************************************************************************/

#if ((PRISEC == SECONDARY) || (PRISEC == PEER))
    BYTE IrDA_CloseCommServer( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_ReadComm( BYTE *dataArray, WORD maxSize, WORD timeout, WORD *dataLength )

  Summary:
    This function initiates a read from the IrDA port.

  Description:
    This function initiates a read from the IrDA port.  The actual read
    is performed in the background.  This function will terminate
    when either the maximum number of characters has been received
    or the timeout expires.

  Precondition:
    IrDA_OpenCommClient/IrDA_OpenCommServer has been called and returned with success.

  Parameters:
    *dataArray  - pointer to the user's buffer
    maxSize     - the maximum number of characters that can be stored
    timeout     - the number of milliseconds for the read to terminate
    *dataLength - number of bytes read

  Return Values:
    0x00 - success (at least some data read)
    0x01 - not connected
    0x04 - timeout, no data

  Remarks:
    If READ_INTO_RAM is not defined, the user must have a
    function uIrDA_StoreDataByte that the callback can use to store
    the received data bytes.
  ***************************************************************************/

BYTE IrDA_ReadComm( BYTE *dataArray, WORD maxSize, WORD timeout, WORD *dataLength );

/****************************************************************************
  Function:
    BYTE IrDA_ReadInitComm( BYTE *dataArray, WORD maxSize, WORD timeout )

  Summary:
    This function initiates a read from the IrDA port.

  Description:
    This function initiates a read from the IrDA port.  The actual read
    is performed in the background.  While the read is in progress,
    IrDA_CommServerBackground should be called to process the stack
    events.  IrDA_ReadResultComm should be called to monitor the
    status of the read.

  Precondition:
    IrDA_OpenCommClient/IrDA_OpenCommServer has been called and returned with success.

  Parameters:
    *dataArray  - pointer to the user's buffer
    maxSize     - the maximum number of characters that can be stored
    timeout     - the number of milliseconds for the read to terminate

  Return Values:
    0x00 - success
    0x01 - not connected

  Remarks:
    If READ_INTO_RAM is not defined, the user must have a
    function uIrDA_StoreDataByte that the callback can use to store
    the received data bytes.
  ***************************************************************************/

BYTE IrDA_ReadInitComm( BYTE *dataArray, WORD maxSize, WORD timeout );

/****************************************************************************
  Function:
    BYTE IrDA_ReadResetComm( void )

  Summary:
    This function resets the variables used to monitor a read operation.

  Description:
    This function resets the variables used to monitor a read operation.
    It should be called after IrDA_ReadResultComm indicates the read
    operation is complete.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - operation complete

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_ReadResetComm( void );

/****************************************************************************
  Function:
    BYTE IrDA_ReadResultComm( WORD *dataLength )

  Summary:
    This function returns the status of a read operation.

  Description:
    This function returns the status of a read operation.  If the
    read operation is complete, then the length of the received
    data is returned.

  Precondition:
    IrDA_OpenCommClient/IrDA_OpenCommServer has been called and returned with success.

  Parameters:
    *dataLength - the number of received bytes

  Return Values:
    IRDA_COMM_READ_COMPLETE         - Read operation is complete, either from
                                        a timeout or from the maximum number
                                        of bytes being received
    IRDA_COMM_READ_NOT_IN_PROGRESS  - No read operation is currently
                                        in progress.  This allows this
                                        function to be called without
                                        requiring IrDA_ReadInitComm to be
                                        called first.
    IRDA_COMM_READ_NOT_COMPLETE     - A read operation is currently in
                                        progress.

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_ReadResultComm( WORD *dataLength );

/****************************************************************************
  Function:
    BYTE IrDA_StackIsActive( void )

  Summary:
    This function indicates whether or not the stack is still
    processing frames.

  Description:
    This function indicates whether or not the stack is still
    processing frames.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 (false) - Stack is not active, all frames have been processed
    1 (true)  - Stack is active, frames are still being processed

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_StackIsActive( void );

/****************************************************************************
  Function:
    BYTE IrDA_WriteComm( BYTE *prt_buf, WORD buf_size )

  Summary:
    This function sends user data out the IrDA port.

  Description:
    This function sends user data out the IrDA port.

  Precondition:
    IrDA_OpenCommClient/IrDA_OpenCommServer has been called and returned with success.

  Parameters:
     *prt_buf - pointer to the user's buffer
     buf_size - number of bytes to transmit

  Return Values:
    0x00 - success
    0x01 - no buffers
    0x41 - no buffers
    0x82 - bad comm_state
    0x9X - X=failure code for LM_Data_request

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_WriteComm( BYTE *prt_buf, WORD buf_size );


