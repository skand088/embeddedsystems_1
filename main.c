/*
 * File:   main.c
 * Author: SIMAR KANDOLA, ABIA JAHANGIR, RINAD HAMID!!!! GROUP 25
 * 
 *
 * Created on: September 19th, 3:49pm
 */

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC oscillator (FRC))
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-Speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output disabled; pin functions as port I/O)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include <p24F16KA101.h>

/**
 * You might find it useful to add your own #defines to improve readability here
 */

#define DELAY_250MS 100000
#define DELAY_1S    150000
#define DELAY_6S   1000000

int buttons_pressed(void) {
    int count = 0;
    if(PORTBbits.RB7 == 0) count++; // PB1
    if(PORTBbits.RB4 == 0) count++; // PB2
    if(PORTAbits.RA4 == 0) count++; // PB3
    return count;
}

void delay_check(unsigned long loops) {
    volatile unsigned long i;
    for(i = 0; i < loops; i++) {
        if(buttons_pressed() >= 2) {
            LATBbits.LATB9 = 1;
            while(buttons_pressed() >= 2);   
            return;                           
        }
    }
}

int main(void) {
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */

    TRISBbits.TRISB9 = 0;  // LED output
    TRISBbits.TRISB7 = 1;  // PB1 input
    TRISBbits.TRISB4 = 1;  // PB2 input
    TRISAbits.TRISA4 = 1;  // PB3 input

    CNPU2bits.CN23PUE = 1; // PB1
    CNPU1bits.CN1PUE  = 1; // PB2
    CNPU1bits.CN0PUE  = 1; // PB3

    while(1) {
        int pressed = buttons_pressed();

        if(pressed >= 2) {
            LATBbits.LATB9 = 1;
        }
        else if(PORTBbits.RB7 == 0) { // PB1
            LATBbits.LATB9 = 1;
            delay_check(DELAY_250MS);
            LATBbits.LATB9 = 0;
            delay_check(DELAY_250MS);
        }
        else if(PORTBbits.RB4 == 0) { // PB2
            LATBbits.LATB9 = 1;
            delay_check(DELAY_1S);
            LATBbits.LATB9 = 0;
            delay_check(DELAY_1S);
        }
        else if(PORTAbits.RA4 == 0) { // PB3
            LATBbits.LATB9 = 1;
            delay_check(DELAY_6S);
            LATBbits.LATB9 = 0;
            delay_check(DELAY_6S);
        }
        else {
            LATBbits.LATB9 = 0;
        }
    }

    return 0;
}