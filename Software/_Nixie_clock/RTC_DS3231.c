#include "rtc_ds3231.h"

extern enum Clock_edit_mode clock_edit_mode;

void rtc_init(void)
{
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);
	i2c_sendbyte(DS3231_STATUS_ADDR);
	i2c_sendbyte(DS3231_STATUS_EN32KHZ);
	i2c_stop();		
}

void rtc_set_time(Time_t *t, uint8_t hour, uint8_t min)
{
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);	
	i2c_sendbyte(DS3231_TIME_MIN_ADDR);
	i2c_sendbyte(dec_to_bin(t->min));
	i2c_sendbyte(dec_to_bin(t->hour));
	i2c_stop();
}

void rtc_get_time(Time_t *t)
{	
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);
	i2c_sendbyte(DS3231_TIME_CAL_ADDR);
	i2c_stop();
	i2c_start();
	i2c_sendbyte(DS3231_READ_ADDR);
	t->sec = i2c_readbyte();
	t->min = i2c_readbyte();
	t->hour = i2c_readbyte();
}

void sqw_set(void)
{
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);
	i2c_sendbyte(DS3231_CONTROL_ADDR);
	/*Bits RS0 RS1 to LOW*/
	i2c_sendbyte(0x00);					
	i2c_stop();
}

void rtc_increment(Time_t *t)
{
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);//передача адреса устройства, режим записи
	switch(clock_edit_mode)
	{
		case MODEHOUREDIT:
			i2c_sendbyte(DS3231_TIME_HOUR_ADDR);//Переходим по адресу 0x02 - часы 
		if(t->hour < 23)
			i2c_sendbyte(dec_to_bin(t->hour + 1));
		else
			i2c_sendbyte(dec_to_bin(0));
		break;
		
		case MODEMINEDIT:
			i2c_sendbyte(DS3231_TIME_MIN_ADDR);
		if(t->min < 59)
			i2c_sendbyte(dec_to_bin(t->min + 1));
		else
			i2c_sendbyte(dec_to_bin(0));
		break;		
	}
	i2c_stop();
}

void rtc_decrement(Time_t *t)
{
	i2c_start();
	i2c_sendbyte(DS3231_WRITE_ADDR);
	switch(clock_edit_mode)
	{
		case MODEHOUREDIT:
			i2c_sendbyte(DS3231_TIME_HOUR_ADDR);
		if(t->hour > 0)
			i2c_sendbyte(dec_to_bin(t->hour - 1));
		else
			i2c_sendbyte(dec_to_bin(0));
		break;
		
		case MODEMINEDIT:
			i2c_sendbyte(DS3231_TIME_MIN_ADDR);
		if(t->min > 0)
			i2c_sendbyte(dec_to_bin(t->min - 1));
		else
			i2c_sendbyte(dec_to_bin(0));
		break;
	}
	i2c_stop();
}

/*Utilities*/
uint8_t dec_to_bin(uint8_t c)
{
	uint8_t ch = ((c/10)<<4)|(c%10);
	return ch;
}

uint8_t bin_to_dec(uint8_t c)
{
	uint8_t ch = ((c>>4)*10+(0b00001111&c));
	return ch;
}