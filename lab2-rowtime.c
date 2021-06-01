/*--------------------------------------------------------
GEORGE MASON UNIVERSITY
ECE 447 - Lab2 Row Timing 
  P2.6 Row Clock
  P2.7 Row Initialization

Date:   Fall 2020
Author: Jens-Peter Kaps

Change Log:
20200912 Initial Version, Jens-Peter Kaps
--------------------------------------------------------*/

#include <msp430.h> 

void delay(void) {
    volatile unsigned loops = 100; // Start the delay counter at 100
    while (--loops > 0);             // Count down until the delay counter reaches 0
}


void main(void)
                      {
    unsigned char rowcnt;                                       // row counter
    WDTCTL = WDTPW | WDTHOLD;                                   // stop watchdog timer
    P2DIR |= (BIT6 | BIT7);                                     // Make Port 2.6 and 2.7 outputs
    P8DIR |= (BIT7);                                            // Make Port 8.7 an output
    P9DIR |= (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6);  // Make Ports 9.0-9.6 outputs
    P2OUT &= ~(BIT6 | BIT7);                                    // Set ports to 0
    P8OUT &= ~(BIT7);                                           // Set ports to 0
    P9OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6); // Set ports to 0
    PM5CTL0 &= ~LOCKLPM5;                                       // Unlock ports from power manager
    unsigned char matrix[8] = {1,
                               3,
                               7,
                               15,
                               31,
                               63,
                               127,
                               255};
    rowcnt = 0;
    while(1)                    // continuous loop
    {
        delay();
        if(P2OUT & BIT6)                 // If row clock 1 -> place breakpoint here
            P2OUT &= ~BIT6;              // Set row clock 0
        else {
            if(rowcnt == 6) {            // if on row 6
                P2OUT |= (BIT6 | BIT7);  // Set row clock and row init 1
            } else {                     // for all other rows
                P2OUT |= BIT6;           // only set row clock 1
                P2OUT &= ~BIT7;          // set row init to 0
            }
            P9OUT = matrix[rowcnt];      // Sending data of matrix to port
            P8OUT = matrix[rowcnt];      // Sending data from matrix to port
            rowcnt++;                    // Incrementing row
            if (rowcnt == 8) {           // if on row 8
                rowcnt = 0;              // Resetting clock
            }
        }
    }
}
