// Manufacture provided device file
#include <msp430.h>
#include "timerA.h"
#include "spi.h"

// Local prototypes
void ConfigureClockModule();


void main(void)
{
	// Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW | WDTHOLD;
	ConfigureClockModule();
	InitializeSPIPortPins();
	ConfigureTimerA();

	//configuring SPI
	UCA0CTL1 |= UCSWRST;
	P1DIR |= BIT4;
	P1DIR |= BIT2;
	P1DIR |= BIT3;
	P1DIR |= BIT5;
	P1SEL |= BIT1 + BIT2 + BIT4;
	P1SEL2 |= BIT1 + BIT2 + BIT4;


	UCA0CTL1 |= UCSSEL_2; //SMCLK
	UCA0CTL0 |= (UCMSB + UCSYNC + UCMST + UCCKPH);
	UCA0BR1 = 0x00;	//divide clock by one
	UCA0BR0 = 0x01;
	UCA0MCTL = 0x00;
	UCA0CTL1 &= ~UCSWRST;

    _BIS_SR(GIE);

    while (1);

    return 0;

}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
