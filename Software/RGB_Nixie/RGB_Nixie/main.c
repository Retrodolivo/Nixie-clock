#include "main.h"

void port_init()
{	
	//����� OC0A 
	DDRB |= (1<<PORTB2);
	PORTB &= ~(1<<PORTB2);
	//����� OC1A 
	DDRB |= (1<<PORTB3);
	PORTB &= ~(1<<PORTB3);
	//����� OC1B
	DDRB |= (1<<PORTB4);
	PORTB &= ~(1<<PORTB4);	
	//������
	DDRD &= ~(1<<PORTD3);
	PORTD |= (1<<PORTD3);
}

void interrupt_init()
{
	GIMSK = (1<<INT1);
	MCUCR = (1<<ISC11);//���������� ����������� �� ���������� ������
}


ISR(INT1_vect)
{
	change_mode();
}

int main(void)
{
	spi_init();
	port_init();
	init_PWM_timer0();
	init_PWM_timer1();
	interrupt_init();
	sei();
    while (1) 
    {
			
	}
		
}	
