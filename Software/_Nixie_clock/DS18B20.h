#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NOID				0xCC /*Skip identification*/
#define T_CONVERT			0x44 /*Initiate temperature convert*/
#define READ_DATA			0xBE /*Transfer data to master*/

#define PORTTEMP	PORTB
#define DDRTEMP		DDRB
#define PINTEMP		PINB
#define BITTEMP		4

void dt_get_tempr(Temp_t *tempr, enum Decimal decimal_num);

#endif /* DS18B20_H_ */