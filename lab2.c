/*--------------------------------------------------------
GEORGE MASON UNIVERSITY
ECE 447 - Lab2 In Lab Extercise
  P1.1 Switch S1
  P1.0 LED1 

Date:   Fall 2020
Author: Jens-Peter Kaps

Change Log:
20200913 Initial Version, Jens-Peter Kaps
--------------------------------------------------------*/
#include <msp430.h>

void delay(void) {
	volatile unsigned loops = 25000; // Start the delay counter at 25,000
	while (--loops > 0);             // Count down until the delay counter reaches 0
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    P2REN |= BIT1;            // Connect resistor on P2.1 to P2OUT
    P9OUT |= BIT5;            // Set output register for P9.5 to '1' -> pullup
    P2DIR &= ~BIT1;           // Make P2.1 an input
    P9DIR |= BIT5;            // Make P9.5 an output
    PM5CTL0 &= ~LOCKLPM5;     // Unlock ports from power manager
	
    for (;;) {
    	delay();              // Run the delay sub-routine
    	if (!(P2IN & BIT1))   // Read the input from P2.1 and check its state
    		P9OUT |= BIT5;    // If the button is pressed, turn on the LED
    	else
    		P9OUT &= ~BIT5;   // If the button isn't pressed, turn off the LED
    }
}
