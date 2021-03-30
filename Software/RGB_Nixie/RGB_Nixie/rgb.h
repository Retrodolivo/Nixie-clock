#ifndef RGB_H_
#define RGB_H_

#include "main.h"

void timer0_PWM_init(void);
void timer1_PWM_init(void);
void turn_off(unsigned char R0, unsigned char G0, unsigned char B0);
void set_color_1(unsigned char R1, unsigned char G1, unsigned char B1);
void set_color_2(unsigned char R2, unsigned char G2, unsigned char B2);
void set_color_3(unsigned char R3, unsigned char G3, unsigned char B3);
void change_color(void);


typedef struct
{
	uint8_t red, green, blue; 	
} Color_t;

#endif /* RGB_H_ */