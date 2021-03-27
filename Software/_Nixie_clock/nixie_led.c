#include "nixie_led.h"

//��������� ������ �� ���������. ������� �155��1
#define A0  PORTD3
#define A1  PORTD1
#define A2  PORTD0
#define A3  PORTD2

unsigned char R1, R2, R3, R4,//������(����� �����)
			  i;
			  
unsigned char clock_edit_mode;
unsigned char clockmode;

//������� ��� ����������� �155��1
void segchar(unsigned char seg)
{
	switch(seg)
	{
		case 0: PORTD &= ~((1<<A2)|(1<<A1)|(1<<A3)|(1<<A0)); break;
		
		case 1: PORTD |= (1<<A0);
				PORTD &= ~((1<<A2)|(1<<A1)|(1<<A3)); break;
				
		case 2: PORTD |= (1<<A1);
				PORTD &= ~((1<<A2)|(1<<A3)|(1<<A0)); break;
				
		case 3: PORTD |= ((1<<A1)|(1<<A0));
				PORTD &= ~((1<<A2)|(1<<A3)); break;
				
		case 4: PORTD |= (1<<A2);
				PORTD &= ~((1<<A1)|(1<<A3)|(1<<A0)); break;	
					  
		case 5: PORTD |= ((1<<A2)|(1<<A0));
				PORTD &= ~((1<<A1)|(1<<A3)); break;

		case 6: PORTD |= ((1<<A2)|(1<<A1));
				PORTD &= ~((1<<A3)|(1<<A0)); break;
				
		case 7: PORTD |= ((1<<A2)|(1<<A1)|(1<<A0));
				PORTD &= ~((1<<A3)); break;

		case 8: PORTD |= (1<<A3);
				PORTD &= ~((1<<A2)|(1<<A1)|(1<<A0)); break;

		case 9: PORTD |= ((1<<A3)|(1<<A0));
				PORTD &= ~((1<<A2)|(1<<A1)); break;
	}	
}

//������ ������� ������������ ���������
void timer_ini(void)
{
	TCCR1B |= (1<<WGM12); // ������������� ����� ��� (����� �� ����������)
	TIMSK |= (1<<OCIE1A);	//������������� ��� ���������� ���������� 1��� �������� �� ���������� � OCR1A(H � L)
	OCR1AH = 0b00001111; //���������� � ������� ����� ��� ���������
	OCR1AL = 0b01000010;
	TCCR1B |= (1<<CS11);//��������� ��������.
}

ISR (TIMER1_COMPA_vect)
{
	if(i == 0)
	{
		PORTC |= 1<<PORTC2; PORTC &= ~((1<<PORTC0)|(1<<PORTC1)|(1<<PORTC3));
		segchar(R4);
		//������� ��������� � ������ ��������������
		if((clock_edit_mode == MODEHOUREDIT)&&(!(PIND&(1<<PIND4))))
			PORTC &= ~(1<<PORTC2);		
	}
	if(i == 1)
	{
		PORTC |= 1<<PORTC1; PORTC &= ~((1<<PORTC0)|(1<<PORTC2)|(1<<PORTC3));
		segchar(R3);
		//������� ��������� � ������ ��������������
		if((clock_edit_mode == MODEHOUREDIT)&&(!(PIND&(1<<PIND4))))
			PORTC &= ~(1<<PORTC1);
	}
	if(i == 2)
	{
		PORTC |= 1<<PORTC3; PORTC &= ~((1<<PORTC0)|(1<<PORTC1)|(1<<PORTC2));
		segchar(R2);
		//������� ��������� � ������ ��������������
		if((clock_edit_mode == MODEMINEDIT)&&(!(PIND&(1<<PIND4))))
			PORTC &= ~(1<<PORTC3);		
	}
	if(i == 3)
	{
		
		PORTC |= 1<<PORTC0; PORTC &= ~((1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3));
		segchar(R1);
		//������� ��������� � ������ ��������������		
		if((clock_edit_mode == MODEMINEDIT)&&(!(PIND&(1<<PIND4))))
			PORTC &= ~(1<<PORTC0);
		if(clockmode == MODETEMPERVIEW)
			PORTC &= ~(1<<PORTC0);		
	}
	if(i == 4)
	{
		//SQW
		if(PIND & (1<<PIND4))
			PORTB |= 1<<PORTB5;
		else if(clockmode != MODETEMPERVIEW)
			PORTB &= ~(1<<PORTB5);
	}
	i++;
	if(i > 4) 
		i = 0;
}

void indicator_display(unsigned int number, unsigned char cm)
{
	clockmode = cm;
	R1 = number%10;
	R2 = number%100/10;
	R3 = number%1000/100;
	R4 = number/1000;	
}