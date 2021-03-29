#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "main.h"

void buttons_port_init(void);
void timer0_buttons_init(void);

extern enum Clock_edit_mode clock_edit_mode;

#define BUTTONS_PORT		PORTB
#define BUTTONS_DDR			DDRB
#define BUTTON_UP			PORTB3
#define BUTTON_DOWN			PORTB1
#define BUTTON_OK			PORTB2

#define BUTTON_UP_PRESSED	(!(PINB&(1<<PINB3)))
#define BUTTON_DOWN_PRESSED	(!(PINB&(1<<PINB1)))
#define BUTTON_OK_PRESSED	(!(PINB&(1<<PINB2)))

#endif /* BUTTONS_H_ */