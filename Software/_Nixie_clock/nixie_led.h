#ifndef NIXIE_LED_H_
#define NIXIE_LED_H_

#include "main.h"

void segchar(unsigned char seg);
void timer_ini(void);
void indicator_display(unsigned int number, unsigned char cm);



#endif /* NIXIE_LED_H_ */