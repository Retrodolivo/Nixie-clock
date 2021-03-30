#include "led.h"

/*IN-12 lamp number*/
unsigned char R1, R2, R3, R4, 
			  lamp_num;

void lamp_port_init(void)
{
	DECODER_DDR |= 1<<A0 | 1<<A1 | 1<<A2 | 1<<A3;
	DECODER_PORT &= ~(1<<A0 | 1<<A1 | 1<<A2 | 1<<A3);
	
	IN_ANODE_DDR |= 1<<IN_R1 | 1<<IN_R2 | 1<<IN_R3 | 1<<IN_R4;
	IN_ANODE_PORT &= ~(1<<IN_R1 | 1<<IN_R2 | 1<<IN_R3 | 1<<IN_R4);
	
	SQW_DDR &= ~(1<<SQW_PIN);
	SQW_PORT &= ~(1<<SQW_PIN);
	
	INS_DDR |= 1<<INS_ANODE;
	INS_PORT &= ~(1<<INS_ANODE);
}
		  
/*
	Decoder K155ID1
	Set A0 - A3 inputs of K155ID1 according seg num
*/
static void segchar(unsigned char seg)
{
	switch(seg)
	{
		case 0: 
			DECODER_PORT &= ~(1<<A2 | 1<<A1 | 1<<A3 | 1<<A0); 
			break;
		
		case 1: 
			DECODER_PORT |=   1<<A0;
			DECODER_PORT &= ~(1<<A2 | 1<<A1 | 1<<A3); 
			break;		
		case 2: 
			DECODER_PORT |=   1<<A1;
			DECODER_PORT &= ~(1<<A2 | 1<<A3 | 1<<A0); 
			break;			
		case 3: 
			DECODER_PORT |=   1<<A1 | 1<<A0;
			DECODER_PORT &= ~(1<<A2 | 1<<A3); 
			break;		
		case 4: 
			DECODER_PORT |=   1<<A2;
			DECODER_PORT &= ~(1<<A1 | 1<<A3 | 1<<A0); 
			break;				  
		case 5: 
			DECODER_PORT |=   1<<A2 | 1<<A0;
			DECODER_PORT &= ~(1<<A1 | 1<<A3); 
			break;
		case 6: 
			DECODER_PORT |=   1<<A2 | 1<<A1;
			DECODER_PORT &= ~(1<<A3 | 1<<A0); 
			break;	
		case 7: 
			DECODER_PORT |=   1<<A2 | 1<<A1 | 1<<A0;
			DECODER_PORT &= ~(1<<A3); 
			break;
		case 8: 
			DECODER_PORT |=   1<<A3;
			DECODER_PORT &= ~(1<<A2 | 1<<A1 | 1<<A0); 
			break;
		case 9: 
			DECODER_PORT |=   1<<A3 | 1<<A0;
			DECODER_PORT &= ~(1<<A2 | 1<<A1); 
			break;
	}	
}
/*
	Dynamic indication timer
	------------------------
	Compare Match Mode(WGM12)
	Interrupt upon OCR1A match
	F(Hz) = (F_CPU / Prescaler) / OCR1A
	F = (8 000 000 / 8) / 3906 = 256(Hz) 	
*/
void timer1_indication_init(void)
{
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1AH = 0xF42 >> 8;
	OCR1AL = 0xF42 & 0xFF;
	/*Prescaler = 8*/
	TCCR1B |= (1<<CS11);
}

/*
	The lamps light up in turn 
	with a frequency of timer1 compare match 	
*/
ISR (TIMER1_COMPA_vect)
{
	switch(lamp_num)
	{
		case 0:
			IN_ANODE_PORT |=   1<<IN_R1;
			IN_ANODE_PORT &= ~(1<<IN_R4 | 1<<IN_R2 | 1<<IN_R3);
			segchar(R1);
			/*Blink R1 R2 at clock edit mode = MODEHOUREDIT*/
			if(clock_edit_mode == MODEHOUREDIT && SQW_PIN_LOW)
				IN_ANODE_PORT &= ~(1<<IN_R1);
			break;
		
		case 1:
			IN_ANODE_PORT |=   1<<IN_R2;
			IN_ANODE_PORT &= ~(1<<IN_R4 | 1<<IN_R1 | 1<<IN_R3);
			segchar(R2);
			/*Blink R1 R2 at clock edit mode = MODEHOUREDIT*/
			if(clock_edit_mode == MODEHOUREDIT && SQW_PIN_LOW)
				IN_ANODE_PORT &= ~(1<<IN_R2);
			break;
		
		case 2:
			IN_ANODE_PORT |=   1<<IN_R3;
			IN_ANODE_PORT &= ~(1<<IN_R4 | 1<<IN_R2 | 1<<IN_R1);
			segchar(R3);
			/*Blink R3 R4 at clock edit mode = MODEMINEDIT*/
			if( clock_edit_mode == MODEMINEDIT && SQW_PIN_LOW)
				IN_ANODE_PORT &= ~(1<<IN_R3);
			break;
		
		case 3:
			IN_ANODE_PORT |=   1<<IN_R4;
			IN_ANODE_PORT &= ~(1<<IN_R2 | 1<<IN_R1 | 1<<IN_R3);
			segchar(R4);
			/*Blink R3 R4 at clock edit mode = MODEMINEDIT*/
			if((clock_edit_mode == MODEMINEDIT)&& SQW_PIN_LOW)
				IN_ANODE_PORT &= ~(1<<IN_R4);
			if(clock_view_mode == MODETEMPERVIEW)
				IN_ANODE_PORT &= ~(1<<IN_R4);
			break;
				
		case 4:
			/*Blink SQW RTC PIN at clock view mode = MODETEMPERVIEW*/
			if(SQW_PIN_HIGH)
				INS_PORT |= 1<<INS_ANODE;
			else if(clock_view_mode != MODETEMPERVIEW)
				INS_PORT &= ~(1<<INS_ANODE);						
	}
	lamp_num++;
	if(lamp_num > 4)
		lamp_num = 0;
}

void display(struct Indication indication, enum Clock_view_mode clock_view_mode)
{
	unsigned int number = 0;
	
	switch(clock_view_mode)
	{
		case MODETIMEVIEW:
			number = indication.t.hour * 100 + indication.t.min;
			break;
		case MODETEMPERVIEW:
			number = (indication.tempr.t_f>>1) * 100 + (indication.tempr.t_f % 2) * 50;
			break;		
	}
	
	R1 = number / 1000;
	R2 = number % 1000 / 100;
	R3 = number % 100 / 10;	
	R4 = number % 10;
}