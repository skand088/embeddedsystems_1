    /*
     * File:   TimeDelay.c
     * Author: Rinad Hamid, Simar Kandola, Abia Jahangir
     *
     * Created on: October 2, 2025
     */

#include <xc.h>
#include <stdint.h>
#include "TimeDelay.h"
#include "clkChange.h"

extern int16_t flag;
void delay_ms(uint16_t time_ms){
    
    newClk(500);  

     uint32_t cycles = (uint32_t)time_ms * 250;  // 250 cycles per ms at 500kHz Fcy

    if (cycles <= 65535) {
        T2CONbits.TCKPS = 00;  // 1:1
        PR2 = cycles - 1;
    }
    else if (cycles / 8 <= 65535) {
        T2CONbits.TCKPS = 01;  // 1:8
        PR2 = (cycles / 8) - 1;
    }
    else if (cycles / 64 <= 65535) {
        T2CONbits.TCKPS = 10;  // 1:64
        PR2 = (cycles / 64) - 1;
    }
    else {
        T2CONbits.TCKPS = 11;  // 1:256
        PR2 = (cycles / 256) - 1;
    }
    
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    T2CONbits.TCS = 0;
    
    TMR2 = 0;
    
    T2CONbits.TON = 1;
    
    IPC1bits.T2IP = 7;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    while (!flag){
        Idle();
    }
    flag = 0;
    return;
}
