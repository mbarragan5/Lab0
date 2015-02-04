/*
* File:   initLab0.c
* Author: Matthew Barragan
*
* Created on January 25, 2015, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

#define FCY 14745600.0
#define TIME_DELAY 1

void initLEDs()
{
    //TODO: Initialize the pin connected to the LEDs as outputs
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;

    //TODO: Turn each LED OFF
    LED4 = OFF;
    LED5 = OFF;
    LED6 = OFF;
    LED7 = OFF;
}

void initSW1()
{
    //TODO: Initialize the pin connected to the switch as an input.
    TRISBbits.TRISB5 = 1;

    IFS1bits.CNIF = 0;

    //Enable the overall change notification interrupt
    IEC1bits.CNIE = 1;

    /* Enable the change notification interrupt for the switch 1 connected to
     * the development board. This corresponds to CN27 according to the PIC24F
     * datasheet. The internal pull-up should not be used for the switch
     * on the development board because one is already there.
     */
    CNEN2bits.CN27IE = 1;
}


void initTimer1()
{
    //TODO: Initialize the timer
    unsigned int prVal = (FCY*TIME_DELAY)/256.0 - 1;
    PR1 = prVal;
    T1CONbits.TCKPS = 0b11; //prescalar 256
    IEC0bits.T1IE = 1; // Enable the interrupt
    IFS0bits.T1IF = 0; // Put the interrupt flag down
    //T1CONbits.TON = 1; // Turn the timer 1 on
}