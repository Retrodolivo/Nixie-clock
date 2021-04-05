#include "rgb.h"

Color_t pink =		{255, 0, 246};
Color_t turquoise =	{30, 255, 243};
Color_t yellow =	{255, 255, 0};
Color_t none =		{0, 0, 0};

void port_init(void)
{
	PWM_DDR |= 1<<PWM_PIN0A | 1<<PWM_PIN1A | 1<<PWM_PIN1B;
	PWM_PORT &= ~(1<<PWM_PIN0A | 1<<PWM_PIN1A | 1<<PWM_PIN1B);
	
	BUTTON_DDR &= ~(1<<BUTTON_PIN);
	BUTTON_PORT |= 1<<BUTTON_PIN;
}

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

static void color_set(Color_t color)
{
	extern float vref;
	/*brightness value [0 .. 1]*/
	float brightness = adc3201_get() * vref;
	
	OCR0A  = color.red * brightness;
	OCR1AL = color.green * brightness;
	OCR1BL = color.blue * brightness;
}

unsigned char i = 0;

void color_change(void)
{	
	switch(i)
	{
		case 0:
			color_set(none);
			i = 1;
			break;
		case 1:
			color_set(pink);
			i = 2;
			break;
		case 2:
			color_set(turquoise);
			i = 3;
			break;
		case 3:
			color_set(yellow);
			i = 0;
			break;
	}
}
