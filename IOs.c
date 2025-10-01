#include <xc.h>

#define LED1 LATBbits.LATB9
#define LED2 LATAbits.LATA6

void IOinit(void) {
    AD1PCFG = 0xFFFF;

    // LED1 outputs
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 0;
  
    // LED2 outputs
    TRISAbits.TRISA6 = 0;
    LATAbits.LATA6 = 0;

    // Pushbuttons
    TRISBbits.TRISB7 = 1; // PB1
    TRISBbits.TRISB4 = 1; // PB2
    TRISAbits.TRISA4 = 1; // PB3

    CNPU2bits.CN23PUE = 1; // PB1
    CNPU1bits.CN1PUE  = 1; // PB2
    CNPU1bits.CN0PUE  = 1; // PB3
}
