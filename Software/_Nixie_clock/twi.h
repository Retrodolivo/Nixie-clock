#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void I2C_init(void);
void I2C_start_condition(void);
void I2C_stop_condition(void);
void I2C_sendbyte(unsigned char c);
unsigned char I2C_readbyte(void);

#endif /* TWI_H_ */