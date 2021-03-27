
#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "nixie_led.h"
#include "twi.h"
#include "RTC_DS3231.h"
#include "button.h"
#include "DS18B20.h"


#define MODETIMEVIEW 100
#define MODETEMPERVIEW 101
#define MODENONEEDIT 10
#define MODEHOUREDIT 11
#define MODEMINEDIT 12

extern unsigned int button_cnt;




#endif /* MAIN_H_ */