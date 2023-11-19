/*
 * main.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Adnan
 */
#include "HAL/LED/hal_led.h"
#include "HAL/BUTTON/hal_button.h"
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"

void INT0_DefaultHandler(void);
void INT1_DefaultHandler(void);
void INT2_DefaultHandler(void);

int main()
{
	led_init(PORTA_INDEX, PIN0);
	led_init(PORTA_INDEX, PIN1);
	led_init(PORTA_INDEX, PIN2);
	button_init(PORTC_INDEX, PIN5);
	button_init(PORTC_INDEX, PIN6);
	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_LOGICAL_CHANGE, INT0_DefaultHandler);
	Interrupr_INTx_Init(EXT_INT1, INTx_SENSE_LOGICAL_CHANGE, INT1_DefaultHandler);
	Interrupr_INTx_Init(EXT_INT2, INTx_SENSE_RISING_EDGE, INT2_DefaultHandler);

	while(1)
	{

	}

	return 0;
}

void INT0_DefaultHandler(void)
{
	led_toggle(PORTA_INDEX, PIN0);
}

void INT1_DefaultHandler(void)
{
	led_toggle(PORTA_INDEX, PIN1);
}

void INT2_DefaultHandler(void)
{
	led_toggle(PORTA_INDEX, PIN2);
}
