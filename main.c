/*
 * main.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Adnan
 */
#include "HAL/LED/hal_led.h"
#include "HAL/BUTTON/hal_button.h"


int main()
{
	uint8_t btn1_val= 0;
	uint8_t btn2_val= 1;
	led_init(PORTA_INDEX, PIN0);
	button_init(PORTC_INDEX, PIN5);
	button_init(PORTC_INDEX, PIN6);

	while(1)
	{
		button_read_state(PORTC_INDEX, PIN5, &btn1_val, BUTTON_STATE_ACTIVE_HIGH);
		button_read_state(PORTC_INDEX, PIN6, &btn2_val, BUTTON_STATE_ACTIVE_LOW);

		if(btn1_val ==BUTTON_PRESSED)
		{
			led_turn_on(PORTA_INDEX, PIN0);
		}
		if(btn2_val ==BUTTON_PRESSED)
		{
			led_turn_off(PORTA_INDEX, PIN0);
		}
	}

	return 0;
}
