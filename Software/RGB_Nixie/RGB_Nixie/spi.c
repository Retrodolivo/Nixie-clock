#include "spi.h"

void spi_init(void)
{
	SPI_DDR |= 1<<SPI_CS | 1<<SPI_DO | 1<<SPI_SCK;
	SPI_DDR &= ~(1<<SPI_DI);
	SPI_PORT &= ~(1<<SPI_CS | 1<<SPI_DO | 1<<SPI_SCK);
}

/*
	Three-wire mode(USIWM0) / DI, DI, SCK
*/
unsigned char spi_change_byte(char byte)
{
	USIDR = byte;
	/*Clear overflow interrupt flag(USIOIF)*/
	USISR |= (1<<USIOIF);
	while(!(USISR & (1<<USIOIF)))
	{
		USICR |= ((1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC));
		_delay_us(10);		
	}
	return USIDR;	
}
