#ifndef IOS_H
#define IOS_H

#include <xc.h>
#include <stdint.h>  

// LED macros
#define LED1 LATBbits.LATB9
#define LED2 LATAbits.LATA6

// Function prototypes
void IOinit(void);
void IOcheck(void);

#endif 
