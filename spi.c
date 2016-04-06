#include "spi.h"

void InitializeSPIPortPins()
{
	/* Note that the SPI functionality is being implemented in software
	 * (that is, "bit banging").  As such, the USCI module is not being used.
	 */
	SET_USCIA0_MOSI_AS_AN_OUTPUT;
	SET_USCIA0_MISO_AS_AN_INPUT;
	INITIALIZE_SPI_SCK;
	SET_SPI_SCK_AS_AN_OUTPUT;
}
//reconfigured SPISendByte method
void SPISendByte(unsigned char byte_value) {
	UCA0TXBUF = byte_value;
	while (UCBUSY & UCA0STAT);
}

unsigned char SPIReceiveByte()
{
	short k;
	unsigned char receive_value = 0;

	// Shift the bits, beginning with the LSB
	for (k = 7; k >= 0; k--){

		// Left-shift the value on MISO k places, and then OR the
		// resulting value with the current value of receive_value.
		receive_value |= (READ_BIT_FROM_SLAVE << k);

		// This commmand should also accomplish the same thing.
		//receive_value = (receive_value << 1) | (READ_BIT_FROM_SLAVE);

		// Toggle SPI Clock: (HIGH XOR 1) -> LOW, and (LOW XOR 1) -> HIGH
		TOGGLE_SPI_SCK; TOGGLE_SPI_SCK;
	}
	return receive_value;
}
