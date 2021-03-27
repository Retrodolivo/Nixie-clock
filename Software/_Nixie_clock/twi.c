#include "twi.h"

void I2C_init(void)
{
	TWBR = 0x20;//устанавливаем частоту работы шины 100к√ц дл€ 8ћ√ц
}

void I2C_start_condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//формируем ¬џ—ќ »… ур на SCL(TWINT), формируем состо€ние —“ј–“(TWSTA), запускаем шину(TWEN)
	while(!(TWCR&(1<<TWINT)));//ждем пока на SCL не установитс€ Ќ»« »… ур
}

void I2C_stop_condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_sendbyte(unsigned char c)
{
	TWDR = c;// c - байт данных
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));//ждем пока на SCL не установитс€ Ќ»« »… ур
}

unsigned char I2C_readbyte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}