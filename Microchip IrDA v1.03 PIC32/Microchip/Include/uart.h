/*

UART Driver Header File for PIC.

********************************************************************************
 FileName:        uart.c
 Dependencies:    HardwareProfile.h
 Processor:       PIC24
 Compiler:        MPLAB C30
 Linker:          MPLAB LINK30
 Company:         Microchip Technology Incorporated

Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Anton Alkhimenok   18-Oct-2005
KO                 11-Oct-2006  v1.0
SS                 14-Dec-2010  Support for generic UART 
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

//******************************************************************************
// Function Prototypes
//******************************************************************************
#if defined(USE_DEBUG_UART1)
   #define IFSxbits_dUxRXIF      IFS0bits.U1RXIF  
   #define dUxRXREG              U1RXREG 
   #define dUxTXREG              U1TXREG 
   #define dUxBRG                U1BRG 
   #define dUxMODE               U1MODE 
   #define dUxMODEbits_BRGH      U1MODEbits.BRGH 
   #define dUxSTA                U1STA 
   #define dUxMODEbits_UARTEN    U1MODEbits.UARTEN 
   #define dUxSTAbits_UTXEN      U1STAbits.UTXEN 
   #define dUxSTAbits_URXEN      U1STAbits.URXEN 
   #define dUxSTAbits_TRMT       U1STAbits.TRMT 
#elif defined(USE_DEBUG_UART2)
   #define IFSxbits_dUxRXIF      IFS1bits.U2RXIF  
   #define dUxRXREG              U2RXREG 
   #define dUxTXREG              U2TXREG 
   #define dUxBRG                U2BRG 
   #define dUxMODE               U2MODE 
   #define dUxMODEbits_BRGH      U2MODEbits.BRGH 
   #define dUxSTA                U2STA 
   #define dUxMODEbits_UARTEN    U2MODEbits.UARTEN 
   #define dUxSTAbits_UTXEN      U2STAbits.UTXEN 
   #define dUxSTAbits_URXEN      U2STAbits.URXEN 
   #define dUxSTAbits_TRMT       U2STAbits.TRMT 
#elif defined(USE_DEBUG_UART3)
   #define IFSxbits_dUxRXIF      IFS1bits.U3RXIF  
   #define dUxRXREG              U3RXREG 
   #define dUxTXREG              U3TXREG 
   #define dUxBRG                U3BRG 
   #define dUxMODE               U3MODE 
   #define dUxMODEbits_BRGH      U3MODEbits.BRGH 
   #define dUxSTA                U3STA 
   #define dUxMODEbits_UARTEN    U3MODEbits.UARTEN 
   #define dUxSTAbits_UTXEN      U3STAbits.UTXEN 
   #define dUxSTAbits_URXEN      U3STAbits.URXEN 
   #define dUxSTAbits_TRMT       U3STAbits.TRMT 
#endif

char UARTxGetChar();
void UARTxInit();
char UARTxIsPressed();
void UARTxPrintString( char *str );
void UARTxPutChar( char ch );
void UARTxPutDec( unsigned char dec );
void UARTxPutHex( int toPrint );

#if defined( __C30__ ) || defined( __PIC32MX__ )
void UARTxPutHexWord( unsigned int toPrint );
#endif
