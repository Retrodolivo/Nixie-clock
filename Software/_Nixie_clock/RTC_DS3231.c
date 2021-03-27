#include "RTC_DS3231.h"

unsigned char clock_edit_mode;

void RTC_init(void)
{
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	I2C_sendbyte(0x0F);//обращаемся к регистру управления по адресу 0x0F
	I2C_sendbyte(0b00001000);//включаем выход на 32кГц
	I2C_stop_condition();		
}

unsigned char dec_to_bin(unsigned char c)
{
	unsigned char ch = ((c/10)<<4)|(c%10);
	return ch;
}

unsigned char bin_to_dec(unsigned char c)
{
	unsigned char ch = ((c>>4)*10+(0b00001111&c));
	return ch;
}

void RTC_set_time(unsigned char hour, unsigned char min)
{
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	
	//ячейки памяти хранения времени
	I2C_sendbyte(0x01);//обращаемся по адресу регистра минут
	I2C_sendbyte(dec_to_bin(min));//устанавливаем значения минут
	I2C_sendbyte(dec_to_bin(hour));//обращаемся по адресу регистра часов, устанавливаем значение
	I2C_stop_condition();
}

void RTC_read_time(void)
{	
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	I2C_sendbyte(0x00);
	I2C_stop_condition();
	I2C_start_condition();
	I2C_sendbyte(0b11010001);//передача адреса устройства, режим чтения
	sec = I2C_readbyte();
	min = I2C_readbyte();
	hour = I2C_readbyte();
}

void SQW_set(void)
{
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	I2C_sendbyte(0x0E);//обращаемся по адресу control register
	I2C_sendbyte(0x00);//биты RS0 RS1 INTCN в 0
	I2C_stop_condition();
}

void Modify_RTC_increment(void)
{
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	switch(clock_edit_mode)
	{
		case MODEHOUREDIT:
			I2C_sendbyte(0x02);//Переходим по адресу 0x02 - часы 
		if(hour < 23)
			I2C_sendbyte(dec_to_bin(hour + 1));
		else
			I2C_sendbyte(dec_to_bin(0));
		break;
		
		case MODEMINEDIT:
			I2C_sendbyte(0x01);//Переходим по адресу 0x01 - минуты 
		if(min < 59)
			I2C_sendbyte(dec_to_bin(min + 1));
		else
			I2C_sendbyte(dec_to_bin(0));
		break;		
	}
	I2C_stop_condition();
}

void Modify_RTC_decrement(void)
{
	I2C_start_condition();
	I2C_sendbyte(0b11010000);//передача адреса устройства, режим записи
	switch(clock_edit_mode)
	{
		case MODEHOUREDIT:
			I2C_sendbyte(0x02);//Переходим по адресу 0x02 - часы
		if(hour > 0)
			I2C_sendbyte(dec_to_bin(hour - 1));
		else
			I2C_sendbyte(dec_to_bin(0));
		break;
		
		case MODEMINEDIT:
			I2C_sendbyte(0x01);//Переходим по адресу 0x01 - минуты
		if(min > 0)
			I2C_sendbyte(dec_to_bin(min - 1));
		else
			I2C_sendbyte(dec_to_bin(0));
		break;
	}
	I2C_stop_condition();
}