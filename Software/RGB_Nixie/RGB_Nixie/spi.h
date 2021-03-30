#ifndef SPI_H_
#define SPI_H_

#include "main.h"

void spi_init(void);
unsigned char spi_change_byte(char byte);

#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_DI		PORTB5	
#define SPI_DO		PORTB6
#define SPI_SCK		PORTB7
#define SPI_CS		PORTB0

#endif /* SPI_H_ */