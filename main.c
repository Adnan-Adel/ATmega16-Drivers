/*
 * mega.c
 *
 * Created: 5/6/2024 3:33:11 PM
 * Author : Adnan
 */ 
/* ------------------------------- Includes ------------------------------- */
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#include "MCAL/TIMERS/TIMER0/mcal_timer0.h"
#include "HAL/LED/hal_led.h"
#include "HAL/SEG/seg.h"

/* ------------------------------- Functions Prototypes ------------------------------- */
void EXT0_Handler(void);
void HAL_Init(void);
void UpdatePedestrianTrafficLight(void);

/* ------------------------------- Data Types ------------------------------- */
typedef enum
{
	OFF,
	RED,
	YELLOW,
	GREEN	
}TrafficLightState_t;

/* ------------------------------- Global Variables ------------------------------- */
static TrafficLightState_t CarLightState = RED;
static TrafficLightState_t PedLightState = OFF;

seg_t my_seg={
	.seg_mode= SEG_COM_ANODE,
	.seg_pins[0]._port= PORTB_INDEX,
	.seg_pins[0]._pin= PIN0,
	.seg_pins[1]._port= PORTB_INDEX,
	.seg_pins[1]._pin= PIN1,
	.seg_pins[2]._port= PORTB_INDEX,
	.seg_pins[2]._pin= PIN2,
	.seg_pins[3]._port= PORTB_INDEX,
	.seg_pins[3]._pin= PIN3,
	.seg_pins[4]._port= PORTB_INDEX,
	.seg_pins[4]._pin= PIN4,
	.seg_pins[5]._port= PORTB_INDEX,
	.seg_pins[5]._pin= PIN5,
	.seg_pins[6]._port= PORTB_INDEX,
	.seg_pins[6]._pin= PIN6,
	.seg_pins[7]._port= PORTB_INDEX,
	.seg_pins[7]._pin= PIN7,
};

Timer0_cfg_t mytimer={
	.Timer0_mode= TIMER0_MODE_NORMAL,
	.Timer0_Preloaded_Value= 6,
	.Timer0_PreScaler= TIMER0_CLOCK_PRESCALER_1,
	.COV= 2000
};


int main(void)
{
	sint8_t counter= 0;
	uint8_t local_state= 0;
	
	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_RISING_EDGE, EXT0_Handler);
	Timer0_Init(&mytimer);
	
	/* Initialize External Hardware Devices */
    HAL_Init();

    while(1)
    {	
		/* Car Traffic Light is in Red State */
		CarLightState= RED;
		led_turn_on(CAR_RED_PORT, CAR_RED_PIN);
		led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
		for(counter= 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			Timer0_WaitBlocking(&mytimer);
		}
		
		/* Car Traffic Light is in Yellow State */
		CarLightState= YELLOW;
		led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
		led_turn_on(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
		if(PedLightState == GREEN)
		{
			for(counter= 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				Timer0_WaitBlocking(&mytimer);
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
			}
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
			PedLightState= RED;
			UpdatePedestrianTrafficLight();
			PedLightState= OFF;
		}
		else if(local_state == 1)
		{
			for(counter= 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				Timer0_WaitBlocking(&mytimer);
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
			}
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
			local_state= 0;
		}
		else
		{
			for(counter= 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				Timer0_WaitBlocking(&mytimer);
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			}
		}
		
		/* Car Traffic Light is in Green State */
		CarLightState= GREEN;
		led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
		led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_on(CAR_GREEN_PORT, CAR_GREEN_PIN);
		for(counter= 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			Timer0_WaitBlocking(&mytimer);
		}
		
		/* Car Traffic Light is in Yellow State */
		CarLightState= YELLOW;
		led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
		led_turn_on(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
		if(PedLightState == RED)
		{
			for(counter= 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				Timer0_WaitBlocking(&mytimer);
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
			}
			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
			local_state= 1;
			PedLightState= OFF;
		}
		else
		{
			for(counter= 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				Timer0_WaitBlocking(&mytimer);
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			}
		}
    }
	
	return 0;
}

void HAL_Init(void)
{
	/* Initialize Pedestrian Traffic Leds */
	led_init(PED_GREEN_PORT, PED_GREEN_PIN);
	led_init(PED_RED_PORT, PED_RED_PIN);
	led_init(PED_YELLOW_PORT, PED_YELLOW_PIN);
	
	/* Initialize Car Traffic Leds */
	led_init(CAR_GREEN_PORT, CAR_GREEN_PIN);
	led_init(CAR_RED_PORT, CAR_RED_PIN);
	led_init(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
	
	/* Initialize Seven Segment */
	seg_init(&my_seg);
}

void EXT0_Handler(void)
{
	uint8_t counter= 0;
	
	switch(CarLightState)
	{
		case RED:
			PedLightState= GREEN;
			UpdatePedestrianTrafficLight();
		break;
		
		case YELLOW:
			PedLightState= RED;
			UpdatePedestrianTrafficLight();
		break;
		
		case GREEN:
			PedLightState= RED;
			UpdatePedestrianTrafficLight();
		break;
	}
}

void UpdatePedestrianTrafficLight(void)
{
	uint8_t counter= 0;
	
	switch(PedLightState)
	{
		case 0:
			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
		break;
		case RED:
			led_turn_on(PED_RED_PORT, PED_RED_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
		break;
		
		case YELLOW:
		led_turn_off(PED_RED_PORT, PED_RED_PIN);
		led_turn_on(PED_YELLOW_PORT, PED_YELLOW_PIN);
		led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
		break;
		
		case GREEN:
			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
		break;
	}
}