#include "timerA.h"
#include <msp430.h>
#include "spi.h"
#include "ArrayValues.h"

//variables to keep track of position in the array
int num1 = 0;
int num2 = 0;

void ConfigureTimerA(void)
{

	//Set up the timer
	TACTL = (TASSEL_2|ID_0|MC_1|TACLR); //SMCLK, don't divide, count up, clear clock
	TACCR0 = 714;
	TACCTL0 |= CCIE;

}


#pragma vector = TIMER0_A0_VECTOR
// Timer a interrupt service routine, add code here for IN LAB
	__interrupt void TimerA0_routine(void)
{
		P1OUT &= ~BIT3; //array 100
		SPISendByte(0x20);
		SPISendByte(array100[num1] >> 8);
		SPISendByte(array100[num1]);
		P1OUT |= BIT3;

		P1OUT &= ~BIT3;		 //array 300
		SPISendByte(0x21);
		SPISendByte(array300[num1] >> 8);
		SPISendByte(array300[num1]);
		P1OUT |= BIT3;

		P1OUT &= ~BIT3;		 //array 500
		SPISendByte(0x22);
		SPISendByte(array500[num1] >> 8);
		SPISendByte(array500[num1]);
		P1OUT |= BIT3;

		P1OUT &= ~BIT3;		 //array 700
		SPISendByte(0x23);
		SPISendByte(array700[num2] >> 8);
		SPISendByte(array700[num2]);
		P1OUT |= BIT3;

		num1++;
		num2++;

		if (num1 == 224) {
			num1 = 0;
		}

		if (num2 == 32) {
			num2 = 0;
		}
}

