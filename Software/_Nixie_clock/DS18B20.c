#include "DS18B20.h"

char dt_testdevice(void) //dt - digital thermometer | определим, есть ли устройство на шине
{
	char stektemp=SREG;//сохраним значение стека
	cli(); //запрещаем прерывания
	char dt;
	DDRTEMP |= 1<<BITTEMP; //притягиваем шину
	_delay_us(485);//задержка как минимум 480 микросекунд
	DDRTEMP &= ~(1<<BITTEMP);//отпускаем шину
	_delay_us(65);//задержка как минимум 60 микросекунд
	if((PINTEMP & (1<<BITTEMP)) ==0x00)//проверяем, ответит ли утройство
		dt=1;//устройство есть
	else dt=1;//устройства нет
	SREG=stektemp;//вернем показания стека на место
	_delay_us(420);//задержка минимум 480 микросекунд, но хватит и 420, т.к. это с учетом времени прошедших команд
	return dt;
}

// функция отправки бита на устройство
void dt_sendbit (char bt)
{
	char stektemp=SREG;//сохраним значение стека
	cli(); //запрещаем прерывания
	DDRTEMP |= 1<<BITTEMP; //притягиваем шину
	_delay_us(2);
	if(bt)
		DDRTEMP &= ~(1<<BITTEMP);//отпускаем шину
	_delay_us(65);
	DDRTEMP &= ~(1<<BITTEMP);//отпускаем шину
	SREG=stektemp;//вернем показания стека на место
}

//функция отправки байта на устройство
void dt_sendbyte(unsigned char bt)
{
	char i;
	for(i = 0; i < 8; i++)//посылаем отдельно каждый бит
	{
		if((bt & (1<<i)) == 1<<i)//посылаем 1
		dt_sendbit(1);
		else//посылаем 0
		dt_sendbit(0);
	}
}

//функция чтения одного бита с устройства
char dt_readbit (void)
{
	char stektemp=SREG;//сохраним значение стека
	cli(); //запрещаем прерывания
	char bt; //переменная хранения бита
	DDRTEMP |= 1<<BITTEMP; //притягиваем шину
	_delay_us(2);
	DDRTEMP &= ~(1<<BITTEMP);//отпускаем шину
	_delay_us(13);
	bt=(PINTEMP & (1<<BITTEMP))>>BITTEMP; //читаем бит
	_delay_us(45);
	SREG=stektemp;//вернем показания стека на место
	return bt;
}

//функция чтения байта с устройства
unsigned char dt_readbyte()
{
	char c=0;
	char i;
	for(i = 0; i < 8; i++)
	c|= dt_readbit()<<i;//читаем бит
	return c;
}

//функция преобразования показаний датчика в температуру
int dt_check(void)
{
	unsigned char bt; //переменная для считывания бита
	unsigned int tt=0;
	if(dt_testdevice()==1)//если устройство нашлось
	{
		dt_sendbyte(NOID);//пропустить идентификацию, тк у нас только одно устройство на шине
		dt_sendbyte(T_CONVERT);//измеряем температуру
		_delay_ms(100);//9 битный режим преобразования - 100ms
		dt_testdevice();//снова используем те же манипуляции с шиной что и при проверке ее присутствия
		dt_sendbyte(NOID);
		dt_sendbyte(READ_DATA);//передадим байты устройству (в первых двух байтах температура)
		bt = dt_readbyte(); //читаем младший бит
		tt = dt_readbyte(); //читаем бит MS
		tt = (tt<<8)|bt;//сдвигаем старший влево, младнший пишем на его место, тем самым получаем общий результат
	}
	return tt;
}

//преобразование температуры в единицы и десятые доли
char converttemp (unsigned int tt)
{
	char t = tt>>3;//сдвиг - целую часть получим сдвинутую 1 байт влево, а дробную в самом младшем байте
	return t;
}

//преобразование температуры в единицы
char convert (unsigned int tt)
{
	char t_check = tt>>4;//отсекаем до целых значений
	return t_check;
}