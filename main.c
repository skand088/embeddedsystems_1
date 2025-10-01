/*
 * File:   main.c
 * Author: UPDATE THIS WITH YOUR GROUP MEMBER NAMES OR POTENTIALLY LOSE POINTS
 *
 * Created on: USE THE INFORMATION FROM THE HEADER MPLAB X IDE GENERATES FOR YOU
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
#include "clkChange.h"
// Remember, you can use the "extern" keyword to access global variables defined in other files
/**
 * extern int16_t flag_from_other_file;
 */

/**
 * You might find it useful to add your own #defines to improve readability here
 */

volatile int led1_should_blink = 0;  // visible in ISR

int main(void) {
    AD1PCFG = 0xFFFF;
    newClk(500);  // 500 kHz system clock

    // Configure LED1
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 0;
    
    
    // pushbuttons 
    TRISBbits.TRISB7 = 1;  // PB1 input
    TRISBbits.TRISB4 = 1;  // PB2 input
    TRISAbits.TRISA4 = 1;  // PB3 input

    CNPU2bits.CN23PUE = 1; // PB1
    CNPU1bits.CN1PUE  = 1; // PB2
    CNPU1bits.CN0PUE  = 1; // PB3


    T2CONbits.T32 = 0;      // 16-bit mode
    T2CONbits.TCKPS = 00; // 1:1 prescaler
    TMR2 = 0;
    PR2 = 62499;            // 0.25 s interval
    IPC1bits.T2IP = 2;      // interrupt priority
    IFS0bits.T2IF = 0;      // clear flag
    IEC0bits.T2IE = 1;      // enable Timer2 interrupt
    T2CONbits.TON = 1;      // start timer

    while(1) {
    if (!PORTBbits.RB7) {
                led1_should_blink = 1;  // pressed -> blink
            } else {
                led1_should_blink = 0;  // not pressed -> LED off
                LATBbits.LATB9 = 0;
            }    }
}

// Timer 2 interrupt
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0;  // clear interrupt flag

    if (led1_should_blink) {
        LATBbits.LATB9 = !LATBbits.LATB9;  // toggle LED1
    }
}
