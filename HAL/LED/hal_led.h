/*
 * hal_led.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Adnan
 */

#ifndef HAL_LED_HAL_LED_H_
#define HAL_LED_HAL_LED_H_

/* ------------------------------- Includes ------------------------------- */
#include "../../MCAL/GPIO/mcal_gpio.h"

/* ------------------------------- Macros Declarations ------------------------------- */


/* ------------------------------- data types declarations ------------------------------- */


/* ----------------------- Software Interfaces Declarations ----------------------- */
/**
 * @brief Initialize Led Pin as Input
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_init(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief Turn on Led(output High on led pin)
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_turn_on(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief Turn off Led(output Low on led pin)
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_turn_off(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief toggle led state
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_toggle(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);


#endif /* HAL_LED_HAL_LED_H_ */
