/*
 * hal_button.c
 *
 *  Created on: Nov 18, 2023
 *      Author: Adnan
 */


/* ------------------------------- Includes ------------------------------- */
#include "hal_button.h"

/* ----------------------- Software Interfaces Definitions ----------------------- */
/**
 * @brief Initialize Led Pin as Input
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void button_init(gpio_port_index_t _btn_port, gpio_pin_index_t _btn_pin)
{
	gpio_pin_set_direction(_btn_port, _btn_pin, INPUT);
}

/**
 * @brief Turn on Led(output High on led pin)
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void button_read_state(gpio_port_index_t _btn_port, gpio_pin_index_t _btn_pin, uint8_t* _btn_state, uint8_t _btn_active_state)
{
	uint8_t l_btn_pressed_state= 0;
	gpio_pin_get_value(_btn_port, _btn_pin, &l_btn_pressed_state);

	if(_btn_active_state == BUTTON_STATE_ACTIVE_HIGH)
	{
		if(l_btn_pressed_state == LOW)
		{
			*_btn_state= BUTTON_NOT_PRESSED;
		}
		else if(l_btn_pressed_state == HIGH)
		{
			*_btn_state= BUTTON_PRESSED;
		}
	}
	else if(_btn_active_state == BUTTON_STATE_ACTIVE_LOW)
	{
		if(l_btn_pressed_state == LOW)
		{
			*_btn_state= BUTTON_PRESSED;
		}
		else if(l_btn_pressed_state == HIGH)
		{
			*_btn_state= BUTTON_NOT_PRESSED;
		}
	}
}
