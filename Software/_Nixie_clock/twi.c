#include "twi.h"

void I2C_init(void)
{
	TWBR = 0x20;//������������� ������� ������ ���� 100��� ��� 8���
}

void I2C_start_condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//��������� ������� �� �� SCL(TWINT), ��������� ��������� �����(TWSTA), ��������� ����(TWEN)
	while(!(TWCR&(1<<TWINT)));//���� ���� �� SCL �� ����������� ������ ��
}

void I2C_stop_condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_sendbyte(unsigned char c)
{
	TWDR = c;// c - ���� ������
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));//���� ���� �� SCL �� ����������� ������ ��
}

unsigned char I2C_readbyte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}