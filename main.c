/*
 * FinalAdnan.c
 *
 * Created: 11/21/2023 12:07:07 AM
 * Author : Adnan
 */ 

#include "MCAL/GPIO/mcal_gpio.h"
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#include "MCAL/USART/mcal_usart.h"
#include "HAL/LED/hal_led.h"
#include "HAL/BUTTON/hal_button.h"
#include "MCAL/TIMERS/TIMER0/mcal_timer0.h"

#define CAR_STATE_RED 0
#define CAR_STATE_FROM_RED_TO_YELLOW 1
#define CAR_STATE_FROM_GREEN_TO_YELLOW 2
#define CAR_STATE_GREEN 3

uint8_t car_leds_iterator=0;

uint8_t car_led_state = 0;
void idle_state();
void EXT_INT0_CallBack(void);

usart_cfg_t my_usart={
		._usart_mode= USART_MODE_ASYNCH,
		._usart_operation_mode= USART_OP_MODE_TX_RX,
		._usart_baudrate= 9600,
		._usart_data_bits= USART_DATA_BITS_8,
		._usart_parity= USART_PARITY_DISABLED,
		._usart_stop_bit= USART_STOP_BITS_1
	};

uint8_t rec_data;
Timer0_cfg_t my_timer={
	/* -------------- Configurations for 1sec delay */
	.Timer0_mode= TIMER0_MODE_NORMAL,
	.TIMER0_CALLBACK= NULL,
	.Timer0_PreScaler= TIMER0_CLOCK_PRESCALER_256,
	.Timer0_Preloaded_Value= 238,
	.COV= 122
};

int main(void)
{
	led_init(ped_red_port,ped_red_pin);
	led_init(ped_yellow_port,ped_yellow_pin);
	led_init(ped_green_port,ped_green_pin);
	
	
	led_init(car_red_port,car_red_pin);
	led_init(car_yellow_port,car_yellow_pin);
	led_init(car_green_port,car_green_pin);
	
	
	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_RISING_EDGE, EXT_INT0_CallBack);

	
	USART_Init(&my_usart);
	
	
	
    led_init(PORTA_INDEX, PIN1);
	Timer0_Init(&my_timer);

    while (1) 
    {
		idle_state();
    }
}



void idle_state(){
	
	//turning off all Leds
	led_turn_off(ped_red_port,ped_red_pin);
	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_off(ped_green_port,ped_green_pin);
	
	led_turn_off(car_red_port,car_red_pin);
	led_turn_off(car_yellow_port,car_yellow_pin);
	led_turn_off(car_green_port,car_green_pin);	
	
	
	//******open red led for 10 seconds******
	car_led_state = CAR_STATE_RED;
	car_leds_iterator=10;
	led_turn_on(car_red_port,car_red_pin);
	while(car_leds_iterator){
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_red_port,car_red_pin);
	
	
	//******toggle yellow led for 4 seconds******
	car_led_state = CAR_STATE_FROM_RED_TO_YELLOW;
	car_leds_iterator=4;
	while(car_leds_iterator){
		led_toggle(car_yellow_port,car_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_yellow_port,car_yellow_pin);


	//******open green led for 10 seconds******
	car_led_state = CAR_STATE_GREEN;
	led_turn_on(car_green_port,car_green_pin);
	car_leds_iterator=10;
	while(car_leds_iterator){
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	led_turn_off(car_green_port,car_green_pin);
	
	
	//******toggle yellow led for 4 seconds******
	car_led_state = CAR_STATE_FROM_GREEN_TO_YELLOW;
	car_leds_iterator=4;
	while(car_leds_iterator){
		led_toggle(car_yellow_port,car_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_yellow_port,car_yellow_pin);

}


/* --------------------------------------- EXT INT0 ISR --------------------------------------- */
void EXT_INT0_CallBack(void)
{
	//check for state of cars' LEDS
	switch(car_led_state){
		case CAR_STATE_RED:
		
			break;
			
		case CAR_STATE_FROM_RED_TO_YELLOW:
			break;
		
		case CAR_STATE_FROM_GREEN_TO_YELLOW:
		
			break;
		
		case CAR_STATE_GREEN:

			break;
	}
	
}



void car_state_green_routine(){

	while(car_leds_iterator){
		led_turn_on(ped_red_port,ped_red_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
		}
	led_turn_off(ped_red_port,ped_red_pin);
	car_leds_iterator=1; //to prevent overflow when returning from interrupt
	
}