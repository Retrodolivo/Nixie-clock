#ifndef RTC_DS3231_H_
#define RTC_DS3231_H_

#include "main.h"

void RTC_init(void);
void RTC_read_time(void);
unsigned char dec_to_bin(unsigned char c);
unsigned char bin_to_dec(unsigned char c);
void RTC_set_time(unsigned char hour, unsigned char min);
void SQW_set(void);
void Modify_RTC_increment(void);
void Modify_RTC_decrement(void);


extern unsigned char sec, min, hour;


#endif /* RTC_DS3231_H_ */