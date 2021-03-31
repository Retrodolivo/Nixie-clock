#include "main.h"


/*
	Interrupt upon HIGH to LOW transition
	Button handler
*/
void interrupt_init()
{
	GIMSK = (1<<INT1);
	MCUCR = (1<<ISC11);
}

static void init_routine()
{
	interrupt_init();
	port_init();
	spi_init();
	timer0_PWM_init();
	timer1_PWM_init();
	sei();		
}

ISR(INT1_vect)
{
	color_change();
}

int main(void)
{
	init_routine();
    while (1) 
    {
			
	}
		
}	
