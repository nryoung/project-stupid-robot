/*******************************************************************************

    Microchip IrDA Standard Stack

Summary:
    This header file provides prototpes and constants to allow the IrDA_PIC24F.c
    file to be compiled with the IrDA Standard Library.

Description:
    IrDA_PIC24F.h - PIC24F IrDA Driver Header File

    This header file provides prototpes and constants to allow the IrDA_PIC24F.c
    file to be compiled without the complete IrDA stack source code.  This file
    must be kept aligned with the IrDA stack source code.

*******************************************************************************/
//DOM-IGNORE-BEGIN
/******************************************************************************

Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
KO                 11-Oct-2006  v1.0
KO                 21-Jun-2006  v1.01
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
// Include Files
//------------------------------------------------------------------------------
#include "irda_def.h"
#include "irdep.h"
#include <p32xxxx.h>
#include <plib.h>

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

#define TRUE    1
#define FALSE   0
#define IOCTL_BAUD  0xaa
#define IOCTL_RX_EN 0x01
#define MAX_OUT_FRAMES      10  /* max lap_out_q size */
#define LOQ_TYPE             5  /* lm_out_q */

#if defined( USE_UART1 )
    // UART1 definitions
    #define UxBRG               U1BRG
    #define UxMODE              U1MODE
    #define UxMODEbits          U1MODEbits
    #define UxRXREG             U1RXREG
    #define UxSTA               U1STA
    #define UxSTAbits           U1STAbits
    #define UxTXREG             U1TXREG

    #define RxIntEnable(enable) mU1RXIntEnable(enable)
    #define RxGetIntEnable()    mU1RXGetIntEnable()
    #define RxGetIntFlag()      mU1RXGetIntFlag()
    #define RxClearIntFlag()    mU1RXClearIntFlag()
    
    #define RxIntFlag           IFS0bits.U1RXIF    
    #define RxIntPriorityReg    IPC6bits.U1IP
    #define RxIntPriorityVal    3

    #define TxIntEnable(enable) mU1TXIntEnable(enable)
    #define TxGetIntEnable()    mU1TXGetIntEnable()
    #define TxGetIntFlag()      mU1TXGetIntFlag()
    #define TxClearIntFlag()    mU1TXClearIntFlag()

    #define TxIntPriorityReg    IPC6bits.U1IP
    #define TxIntPriorityVal    3

    #define _UxSTA_URXDA_MASK  	_U1STA_URXDA_MASK  
    #define _UxSTA_RIDLE_MASK   _U1STA_RIDLE_MASK
    #define _UxSTA_URXEN_MASK   _U1STA_URXEN_MASK
    #define _UxSTA_OERR_MASK    _U1STA_OERR_MASK
    #define _UxSTA_UTXEN_MASK   _U1STA_UTXEN_MASK
    
    #define _IrDAHandler		__ISR(_UART_1_VECTOR, ipl3) UARTHandler 

#elif defined( USE_UART2 )
    // UART2 definitions
    #define UxBRG               U2BRG
    #define UxMODE              U2MODE
    #define UxMODEbits          U2MODEbits
    #define UxRXREG             U2RXREG
    #define UxSTA               U2STA
    #define UxSTAbits           U2STAbits
    #define UxTXREG             U2TXREG

    #define RxIntEnable(enable) mU2RXIntEnable(enable)
    #define RxGetIntEnable()    mU2RXGetIntEnable()
    #define RxGetIntFlag()      mU2RXGetIntFlag()
    #define RxClearIntFlag()    mU2RXClearIntFlag()
    
    #define RxIntFlag           IFS1bits.U2RXIF    
    #define RxIntPriorityReg    IPC8bits.U2IP
    #define RxIntPriorityVal    2

    #define TxIntEnable(enable) mU2TXIntEnable(enable)
    #define TxGetIntEnable()    mU2TXGetIntEnable()
    #define TxGetIntFlag()      mU2TXGetIntFlag()
    #define TxClearIntFlag()    mU2TXClearIntFlag()

    #define TxIntPriorityReg    IPC8bits.U2IP
    #define TxIntPriorityVal    2

    #define _UxSTA_URXDA_MASK  	_U2STA_URXDA_MASK  
    #define _UxSTA_RIDLE_MASK   _U2STA_RIDLE_MASK
    #define _UxSTA_URXEN_MASK   _U2STA_URXEN_MASK
    #define _UxSTA_OERR_MASK    _U2STA_OERR_MASK
    #define _UxSTA_UTXEN_MASK   _U2STA_UTXEN_MASK

    #define _IrDAHandler		__ISR(_UART_2_VECTOR, ipl2) UARTHandler 
#elif defined( USE_UART3 )
    // UART3 definitions
    #define UxBRG               U3BRG
    #define UxMODE              U3MODE
    #define UxMODEbits          U3MODEbits
    #define UxRXREG             U3RXREG
    #define UxSTA               U3STA
    #define UxSTAbits           U3STAbits
    #define UxTXREG             U3TXREG

    #define RxIntEnable(enable) mU3RXIntEnable(enable)
    #define RxGetIntEnable()    mU3RXGetIntEnable()
    #define RxGetIntFlag()      mU3RXGetIntFlag()
    #define RxClearIntFlag()    mU3RXClearIntFlag()
    
    #define RxIntFlag           IFS1bits.U3RXIF        
    #define RxIntPriorityReg    IPC8bits.U3IP
    #define RxIntPriorityVal    2

    #define TxIntEnable(enable) mU3TXIntEnable(enable)
    #define TxGetIntEnable()    mU3TXGetIntEnable()
    #define TxGetIntFlag()      mU3TXGetIntFlag()
    #define TxClearIntFlag()    mU3TXClearIntFlag()

    #define TxIntPriorityReg    IPC8bits.U3AIP
    #define TxIntPriorityVal    2

    #define _UxSTA_URXDA_MASK  	_U3STA_URXDA_MASK  
    #define _UxSTA_RIDLE_MASK   _U3STA_RIDLE_MASK
    #define _UxSTA_URXEN_MASK   _U3STA_URXEN_MASK
    #define _UxSTA_OERR_MASK    _U3STA_OERR_MASK
    #define _UxSTA_UTXEN_MASK   _U3STA_UTXEN_MASK

    #define _IrDAHandler		__ISR(_UART_3_VECTOR, ipl2) UARTHandler 
#else
    #error Definition needed for UART used for IrDA.
#endif

//------------------------------------------------------------------------------
// Data Structures
//------------------------------------------------------------------------------

typedef struct fbuf
{
    struct fbuf *next;  /* ptr to next frame */
    SHORT size;         /* current known size of frame */
    BYTE type;         /* frame type: data, control,... */
    BYTE stat;         /* current frame state */
    BYTE final;        /* used for TTP SAR, if not set (0), indicates the final frame ( M bit = 0  in ttp credit byte )*/
} FBUF;

struct LAP_OUT_Q
{
    FBUF *frame[MAX_OUT_FRAMES];
    BYTE head;
    BYTE tail;
};

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------

#ifdef MINBUF
    #define QUEUE_ADD(q_name,ptr,maxsize) q_name.frame[0]=ptr
    #define QUEUE_FULL(q_name,maxsize) (q_name.frame[0]!=0)
#else
    #define QUEUE_ADD(q_name,ptr,maxsize) \
        q_name.frame[q_name.head]=ptr; \
        q_name.head=(q_name.head+1)%maxsize;
    #define QUEUE_FULL(q_name,maxsize) (((q_name.head+1)%maxsize)==q_name.tail)
#endif

#define BENCH4(ended)
#define OS_YIELD()

#define SYS_DELAY_ND(mstimeout) \
    {                           \
        WORD dstarted; \
        for (dstarted=TimeMS();;) \
        { \
            if (((WORD)(TimeMS()-dstarted)) >= mstimeout) \
                break; \
            OS_YIELD(); \
        } \
        BENCH4(mstimeout); \
    }



#define ENABLE_INTS()   EnableIrDAInterrupts() //SR = ((SR & CPU_PRIORITY_MASK) | CPU_PRIORITY_NORMAL);
#define DISABLE_INTS()  DisableIrDAInterrupts() //SR = ((SR & CPU_PRIORITY_MASK) | CPU_PRIORITY_HIGH);

void DisableIrDAInterrupts( void );
void EnableIrDAInterrupts( void );

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

extern struct LAP_OUT_Q lap_out_q;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

BYTE    RX_Framer(BYTE ch);
SHORT   TX_Framer(void);
WORD    TimeMS(void);
WORD    Xclock(void);

