// ******************************************************************************************* //
//
// File:         lab0.c
// Author: Matthew Barragan
//
// Created on January 25, 2015, 1:31 PM
//*************************************************************************************** //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )



typedef enum stateTypeEnum
{
    //TODO: Define states by name
    LED4ON,
    LED5ON,
    LED6ON,
    LED7ON
} stateType;

volatile stateType currentState;
volatile int next = 0;

int main(void)
{
    //TODO: Finish these functions in the provided c files
    initLEDs();
    initTimer1();
    initSW1();

    currentState = LED4ON;

    while(1)
    {
        //Use a switch statement to define the behavior based on the state
        switch(currentState)
        {
            case LED4ON:
            {
                LED4 = ON;
                LED5 = OFF;
                LED6 = OFF;
                LED7 = OFF;
                break;
            }
            case LED5ON:
            {
                LED4 = OFF;
                LED5 = ON;
                LED6 = OFF;
                LED7 = OFF;
                break;
            }
            case LED6ON:
            {
                LED4 = OFF;
                LED5 = OFF;
                LED6 = ON;
                LED7 = OFF;
                break;
            }
            case LED7ON:
            {
                LED4 = OFF;
                LED5 = OFF;
                LED6 = OFF;
                LED7 = ON;
                break;
            }

        }
        
    }
    return 0;
}

void _ISR _T1Interrupt(void)
{
    //TODO: Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;
    next = next + 1;


    //TODO: Change states if necessary.
    //Make sure if you use any variables that they are declared volatile!
   
}

void _ISR _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;
    if(PORTBbits.RB5 == PRESSED)
    {
        T1CONbits.TON = 1;
    }
    
    if(PORTBbits.RB5 == RELEASED && next > 1)
    {
        next = 0;
        T1CONbits.TON = 0;
        TMR1 = 0;
        if(currentState == LED4ON)
        {
            currentState = LED7ON;
        }
        else if(currentState == LED5ON)
        {
            currentState = LED4ON;
        }
        else if(currentState == LED6ON)
        {
            currentState = LED5ON;
        }
        else if(currentState == LED7ON)
        {
            currentState = LED6ON;
        }
    }
    
    else if(PORTBbits.RB5 == RELEASED && next < 2 )
    {
        T1CONbits.TON = 0;
        TMR1 = 0;
        
        if(currentState == LED4ON)
        {
            currentState = LED5ON;
        }
        else if(currentState == LED5ON)
        {
            currentState = LED6ON;
        }
        else if(currentState == LED6ON)
        {
            currentState = LED7ON;
        }
        else if(currentState == LED7ON)
        {
            currentState = LED4ON;
        }
    }
}
 