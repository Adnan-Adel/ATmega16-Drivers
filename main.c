/*
 * Car.c
 *
 * Created: 11/30/2023 10:09:18 PM
 * Author : Adnan
 */ 

/* ------------------------------------- Includes ------------------------------------- */
#include "MCAL/GPIO/mcal_gpio.h"
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#include "MCAL/TIMERS/TIMER0/mcal_timer0.h"
#include "MCAL/USART/mcal_usart.h"
#include "HAL/LED/hal_led.h"
#include "HAL/BUTTON/hal_button.h"
#include "HAL/DC_MOTOR/hal_dc_motor.h"
#include "HAL/IR/hal_ir.h"


usart_cfg_t my_usart={
	._usart_mode= USART_MODE_ASYNCH,
	._usart_operation_mode= USART_OP_MODE_TX_RX,
	._usart_baudrate= 9600,
	._usart_data_bits= USART_DATA_BITS_8,
	._usart_parity= USART_PARITY_DISABLED,
	._usart_stop_bit= USART_STOP_BITS_1
};

dc_motor_cfg_t motorA={
	.dc_motor_en_port= PORTC_INDEX,
	.dc_motor_en_pin= PIN4,
	.dc_motor_in1_port= PORTC_INDEX,
	.dc_motor_in1_pin= PIN0,
	.dc_motor_in2_port= PORTC_INDEX,
	.dc_motor_in2_pin= PIN1,
};

dc_motor_cfg_t motorB={
	.dc_motor_en_port= PORTC_INDEX,
	.dc_motor_en_pin= PIN5,
	.dc_motor_in1_port= PORTC_INDEX,
	.dc_motor_in1_pin= PIN2,
	.dc_motor_in2_port= PORTC_INDEX,
	.dc_motor_in2_pin= PIN3,
};

uint8_t rec_data;

int main(void)
{
    /* ------------------------------------- Initialization ------------------------------------- */
	USART_Init(&my_usart);
	dc_motor_init(&motorA);
	dc_motor_init(&motorB);
	
    while (1) 
    {
		USART_Blocking_ReceiveByte(&my_usart, &rec_data);
		if(rec_data == 'f')
		{
			dc_motor_move_clock_wise(&motorA);
			dc_motor_move_clock_wise(&motorB);		
		}
		else if(rec_data == 'b')
		{
			dc_motor_move_counter_clock_wise(&motorA);
			dc_motor_move_counter_clock_wise(&motorB);
		}
		else if(rec_data == 'r')
		{
			dc_motor_move_counter_clock_wise(&motorA);
			dc_motor_move_clock_wise(&motorB);
		}
		else if(rec_data == 'l')
		{
			dc_motor_move_clock_wise(&motorA);
			dc_motor_move_counter_clock_wise(&motorB);
		}
		else
		{
			dc_motor_stop(&motorA);
			dc_motor_stop(&motorB);
		}
    }
}

