#include "rgb.h"

unsigned char i = 0;

Color_t pink =		{255, 0, 246};
Color_t turquoise =	{30, 255, 243};
Color_t yellow =	{255, 255, 0};
Color_t none =		{0, 0, 0};

/*
	Timer0 is generating PWM at OC0A(PB2)
	OC0A(PB2) is set on Compare Match and clear at TOP(0xFF)
	F_pwm = F_CPU / Prescaler = 8 000 000 / 8 = 1MHz
*/
void timer0_PWM_init(void)
{
	TCCR0A = 1<<WGM00 | 1<<COM0A0 | 1<<COM0A1;				
	TCCR0B = 1<<CS01;
}

/*
	Timer1 is generating PWM at OC1A(PB3), OC1B(PB4)
	OC1A(PB2) and OC1B(PB4) are set on Compare Match and clear at TOP(0x00FF)
	F_pwm = F_CPU / Prescaler = 8 000 000 / 8 = 1MHz
*/
void timer1_PWM_init(void)
{
	TCCR1A = 1<<COM1A0 | 1<<COM1A1 | 
			 1<<COM1B0 | 1<<COM1B1 | 1<<WGM10;
	TCCR1B = 1<<WGM12 | 1<<CS11;
}

void turn_off(unsigned char R0, unsigned char G0, unsigned char B0)
{
	OCR0A  = adc3201_get()*R0)/5;//red
	OCR1AL = adc3201_get()*G0)/5;//green
	OCR1BL = adc3201_get()*B0)/5;//blue
}

void set_color_1(unsigned char R1, unsigned char G1, unsigned char B1)
{
	OCR0A  = adc3201_get()*R1)/5;//red
	OCR1AL = adc3201_get()*G1)/5;//green
	OCR1BL = adc3201_get()*B1)/5;//blue
}

void set_color_2(unsigned char R2, unsigned char G2, unsigned char B2)
{
	OCR0A  = adc3201_get()*R2)/5;//red
	OCR1AL = adc3201_get()*G2)/5;//green
	OCR1BL = adc3201_get()*B2)/5;//blue
}

void set_color_3(unsigned char R3, unsigned char G3, unsigned char B3)
{
	OCR0A  = adc3201_get()*R3)/5;//red
	OCR1AL = adc3201_get()*G3)/5;//green
	OCR1BL = adc3201_get()*B3)/5;//blue
}

void change_color(void)
{	
	switch(i)
	{
		case 0:
		{
			turn_off(Red0, Green0, Blue0);
			i = 1;
			break;
		}
		case 1:
		{
			set_color_1(Red1, Green1, Blue1);
			i = 2;
			break;
		}
		case 2:
		{
			set_color_2(Red2, Green2, Blue2);
			i = 3;
			break;
		}
		case 3:
		{
			set_color_3(Red3, Green3, Blue3);
			i = 0;
			break;
		}
	}
}
