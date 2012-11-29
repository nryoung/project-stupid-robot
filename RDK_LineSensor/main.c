//-----------------------------------------------------------------------/
//																		*/
//	main.c	--	Main program module for project							*/
//																		*/
//-----------------------------------------------------------------------/
//	Author: 	Dion Moses												*/
//	Copyright 2009, Digilent Inc.										*/
//-----------------------------------------------------------------------/
//  Module Description: 												*/
//																		*/
//	This program is a reference design for the Digilent	Line Sensor
//	Robotic Development Kit (RDK-Line) with the Cerebot 32MX4
//	Microcontroller board.  It uses two timers to drive two motors
//	with output compare	modules.										*/
//																		*/
//-----------------------------------------------------------------------/
//  Revision History:													*/
//																		*/
//	10/01/09(DionM): created											*/
//	12/31/09(StevenH): updated to include light sensor support			*/
//	12/08/10(AaronO): renamed to RDK_LineSensor
//																		*/
//-----------------------------------------------------------------------/

#include <plib.h>
#include "stdtypes.h"
#include "config.h"
#include "MtrCtrl.h"
#include "jan_macros.h"
#include "override_config_bits.h"
#include "buttons.h"


void	DeviceInit(void);
void	AppInit(void);
void	Wait_ms(WORD ms);

/* ------------------------------------------------------------ */
/*				Interrupt Service Routines						*/
/* ------------------------------------------------------------ */
/***	Timer5Handler
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Interrupt service routine for Timer 5 interrupt. Timer 5
**		is used to perform software debouncing of the on-board
**		buttons. It is also used as a time base for updating
**		the on-board LEDs and the Pmod8LD LEDs at a regular interval.
*/

void __ISR(_TIMER_5_VECTOR, ipl7) Timer5Handler(void)
{	
		// Read the raw state of the button pins.
	btnBtn1.stCur = ( prtBtn1 & ( 1 << bnBtn1 ) ) ? stPressed : stReleased;
	btnBtn2.stCur = ( prtBtn2 & ( 1 << bnBtn2 ) ) ? stPressed : stReleased;
	
	// Update state counts.
	btnBtn1.cst = ( btnBtn1.stCur == btnBtn1.stPrev ) ? btnBtn1.cst + 1 : 0;
	btnBtn2.cst = ( btnBtn2.stCur == btnBtn2.stPrev ) ? btnBtn2.cst + 1 : 0;
	
	// Save the current state.
	btnBtn1.stPrev = btnBtn1.stCur;
	btnBtn2.stPrev = btnBtn2.stCur;
	
	// Update the state of button 1 if necessary.
	if ( cstMaxCnt == btnBtn1.cst )
	{
		btnBtn1.stBtn = btnBtn1.stCur;
		btnBtn1.cst = 0;
	}
	
	// Update the state of button 2 if necessary.
	if( cstMaxCnt == btnBtn2.cst )
	{
		btnBtn2.stBtn = btnBtn2.stCur;
		btnBtn2.cst = 0;
	}
	
	mT5ClearIntFlag();
}

/***	ChangeNotice_Handler
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Interrupt service routine for all four light sensors via
**		the change notice interrupt handler. Each time a change in
**		sensor state occurs, this routine is called. It assess current
**		sensor state and determines new duty cycles for both motors
**		to correctly follow a line.
*/


BOOL InTheMiddleOfSomething = fFalse;

void __ISR(_CHANGE_NOTICE_VECTOR, ipl2) ChangeNotice_Handler(void)
{
        if(InTheMiddleOfSomething)
            return;
	BYTE bVal;
	bVal = PORTReadBits(IOPORT_B, BIT_0 | BIT_3);
        Led2;

        
        /******************A front wall is detected******************/
        // 
        if(!FrontSensor && LeftSensor)
        {
            InTheMiddleOfSomething = fTrue;
            Led1;
            Led2Clr;

            //Reverse the motor
            SetRightSpeed(dtcMtrStopped);
            RightReverse; //SetRightDir(prtMtrRightDirClr); //Reverse
            SetRightSpeed(dtcMtrMedium);
            //mCNClearIntFlag();

            //Wait until the turn is executed
            Wait_ms(TURN90);

            //Continue going straight
            SetRightSpeed(dtcMtrStopped);
            RightForward; //SetRightDir(prtMtrRightDirSet); //Forward
            SetRightSpeed(dtcMtrMedium);
            
            Led1Clr;
            InTheMiddleOfSomething = fFalse;
            mCNClearIntFlag();
            return;
        }

        if(LeftSensor)
        {
            InTheMiddleOfSomething = fTrue;
            Led4;
            Led2Clr;
            
            //Run for a few moments to get around the corner
            Wait_ms(TURN90/2);

            //Stop it until the turn is completed
            SetLeftSpeed(dtcMtrStopped);
            Wait_ms(TURN90);

            //Continue going straight and wait to mare sure it can detect the new wall
            SetLeftSpeed(dtcMtrMedium);
            Wait_ms(TURN90/4);

            Led4Clr;
            InTheMiddleOfSomething = fFalse;
        }
        
        /*
	if(LeftSensor && FrontSensor)
	{
            SetLeftSpeed(dtcMtrStopped);
            SetRightSpeed(dtcMtrStopped);
	}
	else
        {
            if(LeftSensor)	//Far left sensor -> hard left
            {
                SetLeftSpeed(dtcMtrMedium);
            }
            if(FrontSensor)	//Far right sensor -> hard right
            {
                SetRightSpeed(dtcMtrMedium);
            }
        }

	*/
	mCNClearIntFlag();
}

int main(void)
{

	BYTE	stBtn1;
	BYTE	stBtn2;

	DeviceInit();
	AppInit();

        
        while(stBtn1!=stPressed && stBtn2!=stPressed)
        {
            mT5IntEnable(fFalse);
            stBtn1 = btnBtn1.stBtn;
            stBtn2 = btnBtn2.stBtn;
            mT5IntEnable(fTrue);
        }

        RightReverse;
        LeftReverse;
        SetLeftSpeed(dtcMtrMedium);
        SetRightSpeed(dtcMtrMedium);

        mCNIntEnable(fTrue);	//Sensors will trigger
        while(fTrue);
}

void DeviceInit()
{
	// Configure left motor direction pin and set default direction.
	trisMtrLeftDirSet	= ( 1 << bnMtrLeftDir );
	prtMtrLeftDirSet	= ( 1 << bnMtrLeftDir );	// forward
	
	// Configure right motor diretion pin and set default direction.
	trisMtrRightDirClr	= ( 1 << bnMtrRightDir );	//modify for JD
	prtMtrRightDirClr	= ( 1 << bnMtrRightDir );	// forward

	// Configure Output Compare 2 to drive the left motor.
	OC2CON	= ( 1 << 2 ) | ( 1 << 1 );	// pwm
	OC2R	= dtcMtrStopped;
	OC2RS	= dtcMtrStopped;

	// Configure Output Compare 3.
	OC3CON = ( 1 << 3 ) | ( 1 << 2 ) | ( 1 << 1 );	// pwm
	OC3R	= dtcMtrStopped;
	OC3RS	= dtcMtrStopped;

	// Configure Timer 2.
	TMR2	= 0;		// clear timer 2 count
	PR2		= 9999;

	// Configure Timer 3.
	TMR3	= 0;
	PR3		= 9999;

	// Start timers and output compare units.
	T2CON		= ( 1 << 15 ) | ( 1 << TCKPS20 )|(1 << TCKPS21);	// timer 2 prescale = 8
	OC2CONSET	= ( 1 << 15 );	// enable output compare module 2
	OC3CONSET	= ( 1 << 15 );	// enable output compare module 3
	T3CON		= ( 1 << 15 ) | ( 1 << TCKPS31 ) | ( 1 << TCKPS30); //timer3 prescale = 8

	// Configure Timer 5.
	TMR5	= 0;
	PR5		= 99; // period match every 100 us
	IPC5SET	= ( 1 << 4 ) | ( 1 << 3 ) | ( 1 << 2 ) | ( 1 << 1 ) | ( 1 << 0 ); // interrupt priority level 7, sub 3
	IFS0CLR = ( 1 << 20);
	IEC0SET	= ( 1 << 20);
	
	// Start timers.
	T5CON = ( 1 << 15 ) | ( 1 << 5 ) | ( 1 << 4 ); // fTimer5 = fPb / 8
	
	// Setup light sensor pins
	PORTSetPinsDigitalIn(IOPORT_B, BIT_0 | BIT_3);
	
	// Change notice configured for CN 2 through 5 for light sensors.
	mCNOpen(CN_ON, (CN2_ENABLE | CN3_ENABLE | CN4_ENABLE | CN5_ENABLE), CN_PULLUP_DISABLE_ALL);
	ConfigIntCN(CHANGE_INT_OFF | CHANGE_INT_PRI_2);
	    
	// Enable multi-vector interrupts.
	INTEnableSystemMultiVectoredInt();
}

void AppInit()
{
    //Enable the LEDs
    trisLed1Clr = ( 1 << bnLed1 );
    prtLed1Clr = ( 1 << bnLed1 );
    trisLed2Clr = (1 << bnLed2 );
    prtLed2Clr = ( 1 << bnLed2 );
    trisLed3Clr = ( 1 << bnLed3 );
    prtLed3Clr = ( 1 << bnLed3 );
    trisLed4Clr = ( 1 << bnLed4 );
    prtLed4Clr = ( 1 << bnLed4 );
}

/* ------------------------------------------------------------ */
/***	Wait_ms
**
**	Synopsis:
**		Wait_ms(WORD)
**
**	Parameters:
**		WORD (range from 0 to 65535)
**
**	Return Values:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Will wait for specified number of milliseconds.  Using a 
**		word variable allows for delays up to 65.535 seconds.  The value
**		in the for statement may need to be altered depending on how your
**		compiler translates this code into AVR assembly.  In assembly, it is
**		possible to generate exact delay values by counting the number of clock
**		cycles your loop takes to execute.  When writing code in C, the compiler
**		interprets the code, and translates it into assembly.  This process is 
**		notoriously inefficient and may vary between different versions of AVR Studio
**		and WinAVR GCC.  A handy method of calibrating the delay loop is to write a 
**		short program that toggles an LED on and off once per second using this 
**		function and using a watch to time how long it is actually taking to
**		complete. 
**
*/

void Wait_ms(WORD delay)
{
	WORD i;
	while(delay > 0)
	{
		for(i = 0; i < 375; i ++)
		{
			;;
		}
		delay -= 1;
	}
}
