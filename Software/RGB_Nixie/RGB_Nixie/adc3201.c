#include "adc3201.h"

static float convert(unsigned int dt)
{
	float dt1;
	dt1=((float)dt*(5))/4096;
	return dt1;
}

float adc3201_get(void)
{
	unsigned int b1, b2;
	
	SPI_PORT &= ~(1<<SPI_CS);
	/*Get two bytes of raw adc data*/
	b1 = spi_change_byte(0);
	b2 = spi_change_byte(0);
	b1 = (b1<<8) | b2;
	b1 <<= 3;
	b1 >>= 4;
	SPI_PORT |= 1<<SPI_CS;
	
	return convert(b1);
}