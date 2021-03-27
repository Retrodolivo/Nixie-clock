#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NOID 0xCC // Пропустить индентификацию
#define T_CONVERT 0x44 // Код измерения температуры
#define READ_DATA 0xBE // Передача байтов ведущему

#define PORTTEMP PORTB
#define DDRTEMP DDRB
#define PINTEMP PINB
#define BITTEMP 4

int dt_check(void); //функция преобразования показаний датчика в температуру
char converttemp (unsigned int tt); //преобразование температуры в единицы и десятые доли
char convert (unsigned int tt); //преобразование температуры в единицы 

#endif /* DS18B20_H_ */