#include "main.h"

unsigned char sec, min, hour;
unsigned char clock_edit_mode;
extern unsigned char clockmode;
unsigned int tt = 0;


void port_ini()
{
	DDRD |= ((1<<DDRD0)|(1<<DDRD1)|(1<<DDRD2)|(1<<DDRD3));
	PORTD = 0x00;
	DDRC |= ((1<<DDRC0)|(1<<DDRC1)|(1<<DDRC2)|(1<<DDRC3));
	PORTC = 0x00;
	
	//обработка выхода SQW
	DDRD &= ~(1<<DDRD4);
	PORTD &= ~(1<<PORTD4);
	
	DDRB |= 1<<DDRB5;
	PORTB &= ~(1<<PORTB5); 
}

int main(void)
{
	clock_edit_mode = MODENONEEDIT;
	button_cnt = 0; //измеритель времени нажатия кнопки
	port_ini();
	button_port_ini();
	button_timer_ini();
	timer_ini();
	sei();
	I2C_init();
	RTC_init();
	SQW_set();
	//RTC_set_time(13,25);//устанавливаем часы, затем минуты
	
    while (1) 
    {
		RTC_read_time();
		sec = bin_to_dec(sec);
		min = bin_to_dec(min);
		hour = bin_to_dec(hour);
		
		tt = converttemp(dt_check());
		
		if((clock_edit_mode != MODENONEEDIT)&&(!(PINB&(1<<PINB3))))
		{
			Modify_RTC_increment();
			_delay_ms(300);
		}
		
		if((clock_edit_mode != MODENONEEDIT)&&(!(PINB&(1<<PINB1))))
		{
			Modify_RTC_decrement();
			_delay_ms(300);
		}
		
		if(clock_edit_mode == MODENONEEDIT)
		{
			if(clockmode == MODETIMEVIEW)
				indicator_display(hour*100 + min, MODETIMEVIEW);
			if(clockmode == MODETEMPERVIEW)
				indicator_display((tt>>1)*100+((tt%2)*50), MODETEMPERVIEW);
		}
		else if((clock_edit_mode == MODEHOUREDIT)||(clock_edit_mode == MODEMINEDIT))
			indicator_display(hour*100 + min, MODETIMEVIEW);
			
		if((sec < 31) || (sec > 34)) 
			clockmode = MODETIMEVIEW;
		else
			clockmode = MODETEMPERVIEW;
		
  
    }
}
