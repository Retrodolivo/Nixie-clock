#include "button.h"

extern unsigned char clock_edit_mode;
unsigned char buttonstate = 0, cnt = 0;

void button_port_ini(void)
{
	DDRB &= ~((1<<DDRB3)|(1<<DDRB2)|(1<<DDRB1));
	PORTB |= (1<<PORTB3)|(1<<PORTB2)|(1<<PORTB1);	
}

void button_timer_ini(void)
{
	TIMSK |= (1<<TOIE0);
	TCCR0 |= (1<<CS02)|(1<<CS00);
}

ISR (TIMER0_OVF_vect)
{
	if(buttonstate == 1)
		cnt++;
	if(cnt > 30)
	{
		buttonstate = 0;
		cnt = 0;
	}
	if((!(PINB&(1<<PINB2)))&&(buttonstate == 0))
	{
		button_cnt++;
	}
	else
		button_cnt = 0;
	
	if(button_cnt > 60)
	{
		if(clock_edit_mode < MODEMINEDIT)
			clock_edit_mode++;
		else
			clock_edit_mode = MODENONEEDIT;
		button_cnt = 0;
		buttonstate = 1;
	}

}