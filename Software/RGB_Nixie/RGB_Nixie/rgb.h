#ifndef RGB_H_
#define RGB_H_

#include "main.h"

void port_init(void);
void timer0_PWM_init(void);
void timer1_PWM_init(void);
void color_change(void);


typedef struct
{
	uint8_t red, green, blue; 	
} Color_t;

typedef struct
{
	Color_t color;		
} RGB_t;


#define PWM_DDR		DDRB
#define PWM_PORT	PORTB
#define PWM_PIN0A	PORTB2
#define PWM_PIN1A	PORTB3
#define PWM_PIN1B	PORTB4

#define BUTTON_DDR	DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN  PORTD3


#endif /* RGB_H_ */