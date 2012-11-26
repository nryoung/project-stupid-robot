/*

Microchip IrDA Standard Stack

IrDA Stack Definitions File

This file defines the constants and data structures that an application will
need when using the Microchip IrDA Standard Stack.  Stack users should include
this file at the top of their application, along with the driver header for
their selected protocol.

Protocol                Header File
-----------------------------------
irCOMM 3-wire raw       IrDA_COMM.h
irCOMM 9-wire cooked    IrDA_COMMX.h
OBEX                    IrDA_OBEX.h

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

#ifndef __IRDEP_H__
#define __IRDEP_H__


//******************************************************************************
// Error Codes
//******************************************************************************

#define IRDA_SUCCESS                0x00
#define IRDA_ERROR                  0x01
#define IRDA_ERROR_LINK_CONNECT     0x01
#define IRDA_ERROR_PACKET_SIZE      0x01
#define IRDA_ERROR_USER_EXIT        0x01
#define IRDA_ERROR_OBEX_MAKE        0x01
#define IRDA_ERROR_APP_CONNECT      0x02
#define IRDA_ERROR_UNKNOWN_PI       0x02
#define IRDA_ERROR_OBEX_SAR_TX      0x02
#define IRDA_ERROR_LINK_TIMEOUT     0x03
#define IRDA_ERROR_OBEX_SERVER_TO   0x03
#define IRDA_ERROR_TIMEOUT          0x04
#define IRDA_ERROR_OBEX_SERVER_RSP  0x04
#define IRDA_ERROR_TTP_DATA_MASK    0x10
#define IRDA_ERROR_COMM             0x40
#define IRDA_ERROR_NO_BUFFERS       0x41
#define IRDA_ERROR_BAD_COMM_STATE   0x42
#define IRDA_ERROR_COMM_CONNECT     0x43
#define IRDA_ERROR_BAD_COMM_SERVICE 0x44
#define IRDA_ERROR_SELECTOR_MASK    0x50
#define IRDA_ERROR_TTP_MASK         0x60
#define IRDA_ERROR_WRITE_MASK       0x80
#define IRDA_ERROR_LAP_LINK         0x1001
#define IRDA_ERROR_REMOTE_SEL       0x1002
#define IRDA_ERROR_OBEX_CONNECT     0x1004
#define IRDA_ERROR_OBEX_TIMEOUT     0x1005
#define IRDA_ERROR_NO_BUF_DISCONN   0x1008
#define IRDA_ERROR_OBEX_SERVER      0x1013


//******************************************************************************
// Configuration
//******************************************************************************

/* CPU memory regions */
#define D_AREA


//******************************************************************************
// Data Types
//******************************************************************************

#include "GenericTypeDefs.h"

// Translate internal stack data types to Microchip standard data types.
#define INT32    LONG
#define UINT32   DWORD
#define UINT16   WORD
#define UMEM     WORD
#define INT16    SHORT
#define MEM      SHORT
#define UBYTE    BYTE

// Error Codes
#define UNSUPPORTED_CLOCK  10
#define CONST const


//******************************************************************************
// Include Files
//******************************************************************************

#include <stdio.h>

#include "IrDA_def.h"


//******************************************************************************
// COMM support data structures and macros
//******************************************************************************

// NOTE - Variables referenced here are values that have been received from the
// remote device.

#if ((IRDA_PROTOCOL_TYPE == IRDA_PROTOCOL_IRCOMM3WIRECOOKED) || (IRDA_PROTOCOL_TYPE == IRDA_PROTOCOL_IRCOMM9WIRECOOKED))

    // Control Parameter Identifiers - for use with IrDA_AddControlParam()

    // 3 wire identifiers

    #define SERVICE_TYPE            0x00
    #define DATA_RATE               0x10
    #define DATA_FORMAT             0x11
    #define FLOW_CONTROL            0x12
    #define XON_XOFF                0x13
    #define ENQ_ACK                 0x14
    #define LINE_STATUS             0x15
    #define BREAK                   0x16

    // 9 wire identifiers

    #define DTE_LINE                0x20
    #define DCE_LINE                0x21
    #define POLL_FOR_LINE           0x22

    // Centronic identifiers

    #define STATUS_QUERY            0x30
    #define SET_BUSY_TO             0x31
    #define IEEE_1284_MODE          0x32
    #define IEEE_1284_DEVID         0x33
    #define SEL_IEEE_1284_MODE      0x34
    #define IEEE_1284_ECP_EPP_TX    0x35
    #define IEEE_STATUS_QUERY_RES   0x38
    #define SET_BUSY_TO_RES         0x39
    #define IEEE_1284_MODE_SUP      0x3a
    #define IEEE_1284_DEVICE_ID     0x3b
    #define SELECT_IEEE_1284_MODE   0x3c


    #define IRDA_SERVICE_TYPE_3WIRE         0x02
    #define IRDA_SERVICE_TYPE_9WIRE         0x04
    #define IRDA_SERVICE_TYPE_CENTRONICS    0x08

    //--------------------------------------------------------------------------
    // Service Type

    typedef union _IRDA_SERVICE_TYPE
    {
        BYTE    Val;
        struct  _IRDA_SERVICE_TYPE_bits
        {
            unsigned int                    : 1;
            unsigned int b3Wire             : 1;
            unsigned int b9Wire             : 1;
            unsigned int bCentronics        : 1;
        } bits;
    } IRDA_SERVICE_TYPE;

    //--------------------------------------------------------------------------
    // Data Format

    typedef union _IRDA_DATA_FORMAT
    {
        BYTE    Val;
        struct  _IRDA_DATA_FORMAT_bits
        {
            unsigned int characterLength    : 2;
            unsigned int stopBits           : 1;
            unsigned int parity             : 2;
        } bits;
    } IRDA_DATA_FORMAT;
    #define IRDA_DATA_FORMAT_INIT       0x03

    #define IRDA_DATA_BITS_5            0x00
    #define IRDA_DATA_BITS_6            0x01
    #define IRDA_DATA_BITS_7            0x02
    #define IRDA_DATA_BITS_8            0x03
    #define IRDA_STOP_BITS_1            0x00
    #define IRDA_STOP_BITS_2            0x01
    #define IRDA_PARITY_NONE            0x00
    #define IRDA_PARITY_ODD             0x01
    #define IRDA_PARITY_EVEN            0x03
    #define IRDA_PARITY_MARK            0x05
    #define IRDA_PARITY_SPACE           0x07

    //--------------------------------------------------------------------------
    // Control Indications

    typedef union   _IRDA_CONTROL_INDICATIONS
    {
        BYTE    Val;
        struct   _IRDA_CONTROL_INDICATIONS_bits
        {
            unsigned int breakIndication    : 1;
            #if (IRDA_PROTOCOL_TYPE == IRDA_PROTOCOL_IRCOMM9WIRECOOKED)
            unsigned int pollLineSettings   : 1;
            #endif
        } bits;
    } IRDA_CONTROL_INDICATIONS;
    #define IRDA_CONTROL_INDICATIONS_INIT   0x00


    extern DWORD                    irdaDataRate;
    extern IRDA_DATA_FORMAT         irdaDataFormat;
    extern BYTE                     irdaXON;
    extern BYTE                     irdaXOFF;
    extern BYTE                     irdaENQ;
    extern BYTE                     irdaACK;
    extern IRDA_CONTROL_INDICATIONS irdaControlIndications;

    #define IrDA_GetCommStatus_DataRate()           irdaDataRate
    #define IrDA_GetCommStatus_DataFormat()         irdaDataFormat
    #define IrDA_GetCommStatus_DataSize()           irdaDataFormat.bits.characterLength
    #define IrDA_GetCommStatus_StopBits()           irdaDataFormat.bits.stopBits
    #define IrDA_GetCommStatus_Parity()             irdaDataFormat.bits.parity
    #define IrDA_GetCommStatus_XON()                irdaXON
    #define IrDA_GetCommStatus_XOFF()               irdaXOFF
    #define IrDA_GetCommStatus_ENQ()                irdaENQ
    #define IrDA_GetCommStatus_ACK()                irdaACK
    #define IrDA_GetCommStatus_Break()              irdaControlIndications.bits.breakIndication
    #define IrDA_GetCommStatus_PollLineSettings()   irdaControlIndications.bits.pollLineSettings

    #define IrDA_ClearPollLineSettings()            irdaControlIndications.bits.pollLineSettings = 0;


    //--------------------------------------------------------------------------
    // Flow Control

    typedef union _IRDA_FLOW_CONTROL
    {
        BYTE    Val;
        struct  _IRDA_FLOW_CONTROL_bits
        {
            unsigned int XON_XOFF_input     : 1;
            unsigned int XON_XOFF_output    : 1;
            unsigned int RTS_CTS_input      : 1;
            unsigned int RTS_CTS_output     : 1;
            unsigned int DSR_DTR_input      : 1;
            unsigned int DSR_DTR_output     : 1;
            unsigned int ENQ_ACK_input      : 1;
            unsigned int ENQ_ACK_output     : 1;
        } bits;
    } IRDA_FLOW_CONTROL;
    #define IRDA_FLOW_CONTROL_INIT                  0x00

    #define IRDA_FLOW_CONTROL_XON_XOFF_input        0x01
    #define IRDA_FLOW_CONTROL_XON_XOFF_output       0x02
    #define IRDA_FLOW_CONTROL_RTS_CTS_input         0x04
    #define IRDA_FLOW_CONTROL_RTS_CTS_output        0x08
    #define IRDA_FLOW_CONTROL_DSR_DTR_input         0x10
    #define IRDA_FLOW_CONTROL_DSR_DTR_output        0x20
    #define IRDA_FLOW_CONTROL_ENQ_ACK_input         0x40
    #define IRDA_FLOW_CONTROL_ENQ_ACK_output        0x80

    extern IRDA_FLOW_CONTROL    irdaFlowControl;

    #define IrDA_GetCommStatus_FlowControl()        irdaFlowControl.Val
    #define IrDA_GetCommStatus_XON_XOFF_input()     irdaFlowControl.bits.XON_XOFF_input
    #define IrDA_GetCommStatus_XON_XOFF_output()    irdaFlowControl.bits.XON_XOFF_output
    #define IrDA_GetCommStatus_RTS_CTS_input()      irdaFlowControl.bits.RTS_CTS_input
    #define IrDA_GetCommStatus_RTS_CTS_output()     irdaFlowControl.bits.RTS_CTS_output
    #define IrDA_GetCommStatus_DSR_DTR_input()      irdaFlowControl.bits.DSR_DTR_input
    #define IrDA_GetCommStatus_DSR_DTR_output()     irdaFlowControl.bits.DSR_DTR_output
    #define IrDA_GetCommStatus_ENQ_ACK_input()      irdaFlowControl.bits.ENQ_ACK_input
    #define IrDA_GetCommStatus_ENQ_ACK_output()     irdaFlowControl.bits.ENQ_ACK_output


    //--------------------------------------------------------------------------
    // Line Status

    typedef union _IRDA_LINE_STATUS
    {
        BYTE    Val;
        struct  _IRDA_LINE_STATUS_bits
        {
            unsigned int                    : 1;
            unsigned int OverrunError       : 1;
            unsigned int ParityError        : 1;
            unsigned int FramingError       : 1;
        } bits;
    } IRDA_LINE_STATUS;
    #define IRDA_LINE_STATUS_INIT                   0x00

    #define IRDA_LINE_STATUS_OverrunError           0x02
    #define IRDA_LINE_STATUS_ParityError            0x04
    #define IRDA_LINE_STATUS_FramingError           0x08

    extern IRDA_LINE_STATUS     irdaLineStatus;

    #define IrDA_GetCommStatus_LineStatus()         irdaLineStatus.Val
    #define IrDA_GetCommStatus_FramingError()       irdaLineStatus.bits.FramingError
    #define IrDA_GetCommStatus_OverrunError()       irdaLineStatus.bits.OverrunError
    #define IrDA_GetCommStatus_ParityError()        irdaLineStatus.bits.ParityError

#endif


#if (IRDA_PROTOCOL_TYPE == IRDA_PROTOCOL_IRCOMM9WIRECOOKED)

    //--------------------------------------------------------------------------
    // DTE Line Status

    typedef union _IRDA_DTE_LINE_STATUS
    {
        BYTE    Val;
        struct  _IRDA_DTE_LINE_STATUS_bits
        {
            unsigned int deltaDTR   : 1;
            unsigned int deltaRTS   : 1;
            unsigned int DTR        : 1;
            unsigned int RTS        : 1;
        } bits;
    } IRDA_DTE_LINE_STATUS;
    #define IRDA_DTE_LINE_STATUS_INIT   0x0C

    extern IRDA_DTE_LINE_STATUS irdaDTELineStatus;

    #define IRDA_DTE_LINE_STATUS_deltaDTR       0x01
    #define IRDA_DTE_LINE_STATUS_deltaRTS       0x02
    #define IRDA_DTE_LINE_STATUS_DTR            0x04
    #define IRDA_DTE_LINE_STATUS_RTS            0x08

    #define IrDA_GetCommStatus_DTE()        irdaDTELineStatus.Val
    #define IrDA_GetCommStatus_deltaDTR()   irdaDTELineStatus.bits.deltaDTR
    #define IrDA_GetCommStatus_deltaRTS()   irdaDTELineStatus.bits.deltaRTS
    #define IrDA_GetCommStatus_DTR()        irdaDTELineStatus.bits.DTR
    #define IrDA_GetCommStatus_RTS()        irdaDTELineStatus.bits.RTS


    //--------------------------------------------------------------------------
    // DCE Line Status

    typedef union _IRDA_DCE_LINE_STATUS
    {
        BYTE    Val;
        struct  _IRDA_DCE_LINE_STATUS_bits
        {
            unsigned int deltaCTS   : 1;
            unsigned int deltaDSR   : 1;
            unsigned int deltaRI    : 1;
            unsigned int deltaCD    : 1;
            unsigned int CTS        : 1;
            unsigned int DSR        : 1;
            unsigned int RI         : 1;
            unsigned int CD         : 1;
        } bits;
    } IRDA_DCE_LINE_STATUS;
    #define IRDA_DCE_LINE_STATUS_INIT   0xF0

    extern IRDA_DCE_LINE_STATUS irdaDCELineStatus;

    #define IRDA_DCE_LINE_STATUS_deltaCTS       0x01
    #define IRDA_DCE_LINE_STATUS_deltaDSR       0x02
    #define IRDA_DCE_LINE_STATUS_deltaRI        0x04
    #define IRDA_DCE_LINE_STATUS_deltaCD        0x08
    #define IRDA_DCE_LINE_STATUS_CTS            0x10
    #define IRDA_DCE_LINE_STATUS_DSR            0x20
    #define IRDA_DCE_LINE_STATUS_RI             0x40
    #define IRDA_DCE_LINE_STATUS_CD             0x80

    #define IrDA_GetCommStatus_DCE()        irdaDCELineStatus.Val
    #define IrDA_GetCommStatus_deltaCTS()   irdaDCELineStatus.bits.deltaCTS
    #define IrDA_GetCommStatus_deltaDSR()   irdaDCELineStatus.bits.deltaDSR
    #define IrDA_GetCommStatus_deltaRI()    irdaDCELineStatus.bits.deltaRI
    #define IrDA_GetCommStatus_deltaCD()    irdaDCELineStatus.bits.deltaCD
    #define IrDA_GetCommStatus_CTS()        irdaDCELineStatus.bits.CTS
    #define IrDA_GetCommStatus_DSR()        irdaDCELineStatus.bits.DSR
    #define IrDA_GetCommStatus_RI()         irdaDCELineStatus.bits.RI
    #define IrDA_GetCommStatus_CD()         irdaDCELineStatus.bits.CD

#endif


#endif
