#ifndef LED_H_
#define LED_H_

#include "main.h"

void lamp_port_init(void);
void timer1_indication_init(void);
void display(struct Indication indication, enum Clock_view_mode clock_view_mode);

extern enum Clock_view_mode clock_view_mode;

/*A0 - A3 = Decoder K155ID1 PINOUTS*/
#define DECODER_PORT	PORTD
#define DECODER_DDR		DDRD
#define A0				PORTD3
#define A1				PORTD1
#define A2				PORTD0
#define A3				PORTD2

/*
	IN-12 is an indication nixie lamp
	INS-1 is an small neon lamp
*/
#define IN_ANODE_PORT	PORTC
#define IN_ANODE_DDR	DDRC
#define IN_R1			PORTC2
#define IN_R2			PORTC1
#define IN_R3			PORTC3
#define IN_R4			PORTC0

#define INS_PORT		PORTB
#define INS_DDR			DDRB
#define INS_ANODE		PORTB5

#define SQW_PORT		PORTD
#define SQW_DDR			DDRD
#define SQW_PIN			PORTB4
#define SQW_PIN_LOW		(!(PIND&(1<<PIND4)))
#define SQW_PIN_HIGH	(PIND&(1<<PIND4))

#endif /* LED_H_ */