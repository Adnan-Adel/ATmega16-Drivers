/*
 * mega.c
 *
 * Created: 5/6/2024 3:33:11 PM
 * Author : Adnan
 */ 

#include "HAL/LED/hal_led.h"
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void EXT0_Handler(void);


int main(void)
{
	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_RISING_EDGE, EXT0_Handler);
	
    led_init(CAR_RED_PORT, CAR_RED_PIN);
    led_init(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
    led_init(CAR_GREEN_PORT, CAR_GREEN_PIN);

    led_init(PED_RED_PORT, PED_RED_PIN);
    led_init(PED_GREEN_PORT, PED_GREEN_PIN);

    while(1)
    {
	    led_turn_on(CAR_RED_PORT, CAR_RED_PIN);
	    led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
	    led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
	    _delay_ms(500);

	    led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
	    led_turn_on(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
	    led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
	    _delay_ms(500);

	    led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
	    led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
	    led_turn_on(CAR_GREEN_PORT, CAR_GREEN_PIN);
	    _delay_ms(500);
    }
	
	return 0;
}

void EXT0_Handler(void)
{
	led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
	_delay_ms(500);
	led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
}