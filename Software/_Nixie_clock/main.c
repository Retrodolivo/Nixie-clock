#include "main.h"

enum i2c_speed_t		speed = Standart;
enum Clock_edit_mode	clock_edit_mode = MODENONEEDIT;
enum Clock_view_mode	clock_view_mode = MODETIMEVIEW;
enum Decimal			decimal_num = One;

Time_t t;
Temp_t tempr;
struct Indication indication;

void init_routine(void)
{
	lamp_port_init();
	buttons_port_init();
	timer0_buttons_init();
	timer1_indication_init();
		
	i2c_init(speed);
	rtc_init();
	sei();
	//RTC_set_time(13,25);
}

int main(void)
{
	init_routine();
	
    while(1) 
    {
		/*Fill data structs*/
		rtc_get_time(&t);		
		dt_get_tempr(&tempr, decimal_num);

		/*Buttons handler*/
		if(clock_edit_mode != MODENONEEDIT && BUTTON_UP_PRESSED)
		{
			rtc_increment(&t);
			_delay_ms(300);
		}
		
		if(clock_edit_mode != MODENONEEDIT && BUTTON_DOWN_PRESSED)
		{
			rtc_decrement(&t);
			_delay_ms(300);
		}
		
		if(clock_edit_mode == MODENONEEDIT)
		{
			if(clock_view_mode == MODETIMEVIEW)
				display(indication, clock_view_mode);
			if(clock_view_mode == MODETEMPERVIEW)
				display(indication, clock_view_mode);
		}
		else
			display(indication, clock_view_mode);
		
		/*Every min show temperature*/	
		if(t.sec < 31 || t.sec > 34) 
			clock_view_mode = MODETIMEVIEW;
		else
			clock_view_mode = MODETEMPERVIEW;
    }
}
