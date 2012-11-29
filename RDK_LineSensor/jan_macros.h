/* 
 * File:   jan_macros.h
 * Author: Jon Petraglia
 *
 * Created on November 28, 2012, 5:15 PM
 */

#ifndef JAN_MACROS_H
#define	JAN_MACROS_H

//The RS does the actual motor. Don't quite know what the R does.
#define SetLeftSpeed(x) OC2R = x; OC2RS	= x;
#define SetRightSpeed(x) OC3R = x; OC3RS = x;
#define LeftSensor (!(bVal & (1 << bnSns1)))
#define FrontSensor (!(bVal & (1 << bnSns4)))
#define Led1 prtLed1Set = (1 << bnLed1);
#define Led2 prtLed2Set = (1 << bnLed2);
#define Led3 prtLed3Set = (1 << bnLed3);
#define Led4 prtLed4Set = (1 << bnLed4);
#define Led1Clr prtLed1Clr = (1 << bnLed1);
#define Led2Clr prtLed2Clr = (1 << bnLed2);
#define Led3Clr prtLed3Clr = (1 << bnLed3);
#define Led4Clr prtLed4Clr = (1 << bnLed4);
#define SetRightDir(x) OC4CONCLR	= ( 1 << 15 );\
        x = ( 1 << bnMtrRightDir );\
        OC4CONSET	= ( 1 << 15 );
#define SetLeftDir(x) OC1CONCLR	= ( 1 << 15 );\
        x = ( 1 << bnMtrLeftDir );\
        OC1CONSET	= ( 1 << 15 );
#define LeftReverse SetLeftDir(prtMtrLeftDirSet); //Forward
#define LeftForward SetLeftDir(prtMtrLeftDirClr); //Backward
#define RightReverse SetRightDir(prtMtrRightDirClr); //Forward
#define RightForward SetRightDir(prtMtrRightDirSet); //Forward
#define TURN90 2500

#define	dtcMtrSlow		2500//2500
#define	dtcMtrMedium            4000//4000
#define	dtcMtrFast		8000//8000

#endif	/* JAN_MACROS_H */

