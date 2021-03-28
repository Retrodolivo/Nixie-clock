#include "ds18b20.h"

/*dt - digital thermometer
  find device
*/
char dt_testdevice(void)
{
	/*Save to stack*/
	char stacktemp = SREG;
	cli();
	char dt;
	DDRTEMP |= 1<<BITTEMP;
	_delay_us(485);
	DDRTEMP &= ~(1<<BITTEMP);
	_delay_us(65);
	/*Check if sensor responds*/
	if((PINTEMP & (1<<BITTEMP)) == 0x00)
		dt = 1;
	else 
		dt = 1;
	/*Return stack value*/
	SREG = stacktemp;
	_delay_us(420);
	return dt;
}

void dt_sendbit (char bt)
{
	/*Save to stack*/
	char stacktemp = SREG;
	cli();
	DDRTEMP |= 1<<BITTEMP;
	_delay_us(2);
	if(bt)
		DDRTEMP &= ~(1<<BITTEMP);
	_delay_us(65);
	DDRTEMP &= ~(1<<BITTEMP);
	/*Return stack value*/
	SREG = stacktemp;
}

void dt_sendbyte(unsigned char bt)
{
	char i;
	for(i = 0; i < 8; i++)
	{
		if((bt & 1<<i) == 1<<i)
			dt_sendbit(1);
		else
			dt_sendbit(0);
	}
}


char dt_readbit(void)
{
	/*Save to stack*/	
	char stacktemp = SREG;
	cli();
	char bt;
	DDRTEMP |= 1<<BITTEMP;
	_delay_us(2);
	DDRTEMP &= ~(1<<BITTEMP);
	_delay_us(13);
	bt = (PINTEMP & 1<<BITTEMP)>>BITTEMP;
	_delay_us(45);
	/*Return stack value*/
	SREG = stacktemp;
	return bt;
}

unsigned char dt_readbyte()
{
	char c = 0;
	char i;
	for(i = 0; i < 8; i++)
	c |= dt_readbit()<<i;
	return c;
}

/*raw data to temperature*/
int dt_check(Temp_t *tempr)
{
	unsigned char bt;
	if(dt_testdevice() == 1)
	{
		/*Skip identification*/
		dt_sendbyte(NOID);
		/*Start temperature measurement*/
		dt_sendbyte(T_CONVERT);
		/*9 bits conversins - so 100ms*/
		_delay_ms(100);
		dt_testdevice();
		dt_sendbyte(NOID);
		/*Send data to master*/
		dt_sendbyte(READ_DATA);
		/*Read LSB*/
		bt = dt_readbyte();
		/*Read MSB*/
		tempr->t_raw = dt_readbyte();
		tempr->t_raw = tempr->t_raw<<8 | bt;
	}
	return tempr->t_raw;
}

/*convert to float-like - XX.X °C*/
char converttemp(unsigned int t_raw)
{
	char t_f = t_raw>>3;
	return t_f;
}

/*convert to integer-like - XX °C*/
char convert(unsigned int t_raw)
{
	char t_int = t_raw>>4;
	return t_int;
}
