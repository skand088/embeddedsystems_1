    /*
     * File:   IOs.c
     * Author: Rinad Hamid, Simar Kandola, Abia Jahangir
     *
     * Created on: October 2, 2025
     */


#include <xc.h>
#include "TimeDelay.h"
#include "IOs.h"
#include "clkChange.h"

//define LED pins for easier reference
#define LED1 LATBbits.LATB9
#define LED2 LATAbits.LATA6

void IOinit(void) {
    
    newClk(500);      //set clock frequency to 500 kHz
    AD1PCFG = 0xFFFF;  //set all analog pins to digital

     //configure LED1 as output and turn it off
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 0;
  
    //configure LED2 as output and turn it off
    TRISAbits.TRISA6 = 0;
    LATAbits.LATA6 = 0;

    //configure pushbuttons as inputs
    TRISBbits.TRISB7 = 1; // PB1
    TRISBbits.TRISB4 = 1; // PB2
    TRISAbits.TRISA4 = 1; // PB3
    
    //enable internal pull-up resistors for the pushbuttons
    CNPU2bits.CN23PUE = 1; // PB1
    CNPU1bits.CN1PUE  = 1; // PB2
    CNPU1bits.CN0PUE  = 1; // PB3
}

void IOcheck(void) {
    if(!PORTBbits.RB7 && !PORTBbits.RB4) {      // PB1 + PB2 = 1 ms blink
        LED1 = 1;
        delay_ms(1);
        LED1 = 0;
        delay_ms(1);
    }
    else if(!PORTBbits.RB7) {                   // PB1 = 0.25 s blink
        LED1 = 1;
        delay_ms(250);
        LED1 = 0;
        delay_ms(250);
    }
    else if(!PORTBbits.RB4) {                   // PB2 = 1 s blink
        LED1 = 1;
        delay_ms(1000);
        LED1 = 0;
        delay_ms(1000);
    }
    else if(!PORTAbits.RA4) {                   // PB3 = 6 s blink
        LED1 = 1;
        delay_ms(6000);
        LED1 = 0;
        delay_ms(6000);
    }
    else {
        LED1 = 0;  // No PB pressed LED is off
    }
}



