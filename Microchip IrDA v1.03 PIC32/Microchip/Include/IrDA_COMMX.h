/*******************************************************************************


    Microchip IrDA Standard Stack

Summary:
    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the irCOMM 9-wire cooked
    protocol.
Description:
    IrDA_COMMX.h - IrDA Stack irCOMM 9-wire Cooked Protocol Definitions File

    This file defines the constants and function prototypes that an application will
    need when using the Microchip IrDA Standard Stack with the irCOMM 9-wire cooked
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

#define IRDA_COMMX_READ_COMPLETE            0   // Return code for IrDA_ReadResultCommX.
#define IRDA_COMMX_READ_NOT_IN_PROGRESS     1   // Return code for IrDA_ReadResultCommX.
#define IRDA_COMMX_READ_NOT_COMPLETE        2   // Return code for IrDA_ReadResultCommX.

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/****************************************************************************
  Function:
    BYTE IrDA_AddControlParam( BYTE pi, DWORD pv )

  Summary:
    Use this function to add a control parameter to a data packet
    being prepared for transmission.

  Description:
    Use this function to add a control parameter to a data packet
    being prepared for transmission.

  Precondition:
    See below

  Parameters:
    pi - parameter identifier
    pv - parameter value

  Return Values:
    0 - success
    1 - max packet size exceeded, operation aborted
    2 - unknown parameter identifier

  Remarks:
    Extra steps are needed due to the control channel.  To send a
    packet, do the following:
    <code>
        IrDA_InitCommXDataPacket
        if sending control parameters
            IrDA_StartControlParamList
            for each control parameter
                IrDA_AddControlParam
            endfor
            IrDA_FinishControlParamList
        else
            IrDA_NoControlParameters
        endif
        IrDA_WriteCommX
    </code>
  ***************************************************************************/

BYTE IrDA_AddControlParam( BYTE pi, DWORD pv );

/****************************************************************************
  Function:
    BYTE IrDA_CommXBackground( void )

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

BYTE IrDA_CommXBackground( void );

/****************************************************************************
  Function:
    BYTE IrDA_CommXInit( void )

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

BYTE IrDA_CommXInit( void );

/****************************************************************************
  Function:
    BYTE IrDA_CommXTerminate( void )

  Summary:
    This function terminates the stack, turning off the clock and
    the UART.

  Description:
    This function terminates the stack, turning off the clock and
    the UART.  After this function is called, IrDA_CommXInit() must
    be called to restart the stack.

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

BYTE IrDA_CommXTerminate( void );

//DOM-IGNORE-BEGIN
#define Irda_CommXTerminate IrDA_CommXTerminate
//DOM-IGNORE-END

/****************************************************************************
  Function:
    BYTE IrDA_CloseCommXClient( WORD timeout )

  Summary:
    This function disconnects the IrDA COMMX client.

  Description:
    This function disconnects the IrDA COMMX client.

  Precondition:
    IrDA_OpenCommXClient has been called and returned with success.

  Parameters:
    None

  Return Values:
    0x00 - success
    0x04 - failure

  Remarks:
    After this function is called, IrDA_OpenCommXClient
    can be called without having to call IrDA_CommXInit.
  ***************************************************************************/

#if ((PRISEC == PRIMARY) || (PRISEC == PEER))
    BYTE IrDA_CloseCommXClient( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_CloseCommXServer( WORD timeout )

  Summary:
    This function disconnects the IrDA COMMX server.

  Description:
    This function disconnects the IrDA COMMX server.

  Precondition:
    IrDA_OpenCommXServer has been called and returned with success.

  Parameters:
    None

  Return Values:
    0x00 - success
    0x04 - failure

  Remarks:
    After this function is called, IrDA_OpenCommXServer can be called
    without having to call IrDA_CommXInit.
  ***************************************************************************/

#if ((PRISEC == PRIMARY) || (PRISEC == PEER))
    BYTE IrDA_CloseCommXServer( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_FinishControlParamList(void)

  Summary:
    Finalizes the control parameter list.

  Description:
    Finalizes the control parameter list.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success
    1 - max size exceeded

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_FinishControlParamList(void);

/****************************************************************************
  Function:
    BYTE IrDA_InitCommXDataPacket( void )

  Summary:
    Use this function to initialize a data packet for transmission.

  Description:
    Use this function to initialize a data packet for transmission.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success
    (0x41) 1 - no buffers available

  Remarks:
    Extra steps are needed due to the control channel.  To send a
    packet, do the following:
    <code>
        IrDA_InitCommXDataPacket
        if sending control parameters
            IrDA_StartControlParamList
            for each control parameter
                IrDA_AddControlParam
            endfor
            IrDA_FinishControlParamList
        else
            IrDA_NoControlParameters
        endif
        IrDA_WriteCommX
    </code>
  ***************************************************************************/

BYTE IrDA_InitCommXDataPacket( void );

/****************************************************************************
  Function:
    BYTE IrDA_NoControlParameters(void)

  Summary:
    Sets the control parameter list to no parameters.

  Description:
    Sets the control parameter list to no parameters.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_NoControlParameters(void);

/****************************************************************************
  Function:
    BYTE IrDA_OpenCommXClient( void )

  Summary:
    This function tries to establish a client IrDA connection with
    another device.

  Description:
    This function tries to establish a client IrDA connection with
    another device.

  Precondition:
    IrDA_CommXInit has been called and returned with success.

  Parameters:
    None

  Return Values:
    0x00 - success
    0x41 - no buffers
    0x42 - bad comm_state
    0x43 - comm service connect timeout
    0x44 - comm service disconnected and is unsupported
    0x5X where X - Get_remote_sel error code
    0x6X where X - TTP_Connect_request error code

  Remarks:
    None
  ***************************************************************************/

#if ((PRISEC == PRIMARY) || (PRISEC == PEER))
    BYTE IrDA_OpenCommXClient( void );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_OpenCommXServer( WORD timeout )

  Summary:
    This function tries to establish a server IrDA connection with
    another device.

  Description:
    This function tries to establish a server IrDA connection with
    another device.

  Precondition:
    IrDA_CommXInit has been called and returned with success.

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
    BYTE IrDA_OpenCommXServer( WORD timeout );
#endif

/****************************************************************************
  Function:
    BYTE IrDA_ReadCommX( BYTE *dataArray, WORD maxSize, WORD timeout, WORD *dataLength )

  Summary:
    This function initiates a read from the IrDA port.

  Description:
    This function initiates a read from the IrDA port.  The actual read
    is performed in the background.  This function will terminate
    when either the maximum number of characters has been received
    or the timeout expires.

  Precondition:
    IrDA_OpenCommXClient/IrDA_OpenCommXServer has been called and returned with
                    success.

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

BYTE IrDA_ReadCommX( BYTE *dataArray, WORD maxSize, WORD timeout, WORD *dataLength );

/****************************************************************************
  Function:
    BYTE IrDA_ReadInitCommX( BYTE *dataArray, WORD maxSize, WORD timeout )

  Summary:
    This function initiates a read from the IrDA port.

  Description:
    This function initiates a read from the IrDA port.  The actual read
    is performed in the background.  While the read is in progress,
    IrDA_CommXServerBackground should be called to process the stack
    events, and IrDA_ReadResultCommX should be called to monitor the
    status of the read.

  Precondition:
    IrDA_OpenCommXClient/IrDA_OpenCommXServer has been called and returned with
    success.

  Parameters:
    *dataArray - pointer to the user's buffer
    maxSize - the maximum number of characters that can be stored
    timeout - the number of milliseconds for the read to terminate

  Return Values:
    0x00 - success
    0x01 - not connected

  Remarks:
    If READ_INTO_RAM is not defined, the user must have a
    function uIrDA_StoreDataByte that the callback can use to store
    the received data bytes.
  ***************************************************************************/

BYTE IrDA_ReadInitCommX( BYTE *dataArray, WORD maxSize, WORD timeout );

/****************************************************************************
  Function:
    BYTE IrDA_ReadResetCommX( void )

  Summary:
    This function resets the variables used to monitor a read operation.

  Description:
    This function resets the variables used to monitor a read operation.
    It should be called after IrDA_ReadResultCommX indicates the read
    operation is complete and the application layer retrieves the data.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_ReadResetCommX( void );

/****************************************************************************
  Function:
    BYTE IrDA_ReadResultCommX( WORD *dataLength )

  Summary:
    This function returns the status of a read operation.

  Description:
    This function returns the status of a read operation.  If the
    read operation is complete, then the length of the received
    data is returned.

  Precondition:
    IrDA_OpenCommXClient/IrDA_OpenCommXServer has been called and returned with
    success

  Parameters:
    *dataLength - the number of received bytes

  Return Values:
    IRDA_COMMX_READ_COMPLETE        - Read operation is complete, either from
                                        a timeout or from the maximum number
                                        of bytes being received
    IRDA_COMMX_READ_NOT_IN_PROGRESS - No read operation is currently
                                        in progress.  This allows this
                                        function to be called without
                                        requiring IrDA_ReadInitCommX to be
                                        called first.
    IRDA_COMMX_READ_NOT_COMPLETE    - A read operation is currently in
                                        progress.

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_ReadResultCommX( WORD *dataLength );

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
    0 (false)   - Stack is not active, all frames have been processed
    1 (true)    - Stack is active, frames are still being processed

  Remarks:
  ***************************************************************************/

BYTE IrDA_StackIsActive( void );

/****************************************************************************
  Function:
    BYTE IrDA_StartControlParamList(void)

  Summary:
    Initializes the control parameter list.

  Description:
    Initializes the control parameter list.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    0 - success

  Remarks:
    None
  ***************************************************************************/

BYTE IrDA_StartControlParamList(void);

/****************************************************************************
  Function:
    BYTE IrDA_WriteCommX( BYTE *prt_buf, WORD buf_size )

  Summary:
    Use this function to transmit a data packet.

  Description:
    Use this function to transmit a data packet.  The data to
    transmit is passed into this function; the control channel
    has already been set up as described below.

  Precondition:
    See below

  Parameters:
    *prt_buf - pointer to user data
    buf_size - number of characters of user data

  Return Values:
    0       - success
    1       - data size too large (check control parameters)
    2       - bad comm_state;
    0x1X    - X=failure code for TTP_Data_request

  Remarks:
    Extra steps are needed due to the control channel.  To send a
    packet, do the following:
    <code>
        IrDA_InitCommXDataPacket
        if sending control parameters
            IrDA_StartControlParamList
            for each control parameter
                IrDA_AddControlParam
            endfor
            IrDA_FinishControlParamList
        else
            IrDA_NoControlParameters
        endif
        IrDA_WriteCommX
    </code>
  ***************************************************************************/

BYTE IrDA_WriteCommX( BYTE *prt_buf, WORD buf_size );

