#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

enum Clock_edit_mode
{
	MODENONEEDIT,
	MODEHOUREDIT,
	MODEMINEDIT
};

enum Clock_view_mode
{
	MODETIMEVIEW,
	MODETEMPERVIEW
};

enum Decimal
{
	Zero,
	One,
	Two	
};

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
} Time_t;

typedef struct
{
	unsigned int t_raw;
	char t_f;
	char t_int;
} Temp_t;

struct Indication 
{
	Time_t t;
	Temp_t tempr;
};

#include "rtc_ds3231.h"
#include "i2c.h"
#include "led.h"
#include "buttons.h"
#include "ds18b20.h"



#endif /* MAIN_H_ */