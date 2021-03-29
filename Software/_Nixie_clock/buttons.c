#include "buttons.h"

uint8_t buttonstate = 0, cnt = 0;
uint32_t button_cnt = 0;

void buttons_port_init(void)
{
	BUTTONS_DDR	&= ~(1<<BUTTON_UP | 1<<BUTTON_OK | 1<<BUTTON_DOWN);
	BUTTONS_PORT |= 1<<BUTTON_UP | 1<<BUTTON_OK | 1<<BUTTON_DOWN;	
}

/*
	F_interrut = (F_CPU / Prescaler) / 2^8 = 30Hz
*/
void timer0_buttons_init(void)
{
	/*Interrupt upon overflow(TOIE0)*/
	TIMSK |= (1<<TOIE0);
	/*Prescaler is 1024*/
	TCCR0 |= (1<<CS02)|(1<<CS00);
}

/*
	Button_ok state is polling every interrupt.
	if it would be PRESSED for more than button_cnt ticks SO clock_edit_mode will switch
*/
ISR (TIMER0_OVF_vect)
{
	if(buttonstate == 1)
		cnt++;
	if(cnt > 30)
	{
		buttonstate = 0;
		cnt = 0;
	}
	if(BUTTON_OK_PRESSED && buttonstate == 0)
		button_cnt++;
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