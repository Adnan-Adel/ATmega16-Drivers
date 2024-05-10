/*
 * mega.c
 *
 * Created: 5/6/2024 3:33:11 PM
 * Author : Adnan
 */ 
/* ------------------------------- Includes ------------------------------- */
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#include "MCAL/TIMERS/TIMER0/mcal_timer0.h"
#include "MCAL/SPI/spi.h"
#include "HAL/LED/hal_led.h"
#include "HAL/SEG/seg.h"

/* ------------------------------- Functions Prototypes ------------------------------- */
void EXT0_Handler(void);
void HAL_Init(void);

/* ------------------------------- Data Types ------------------------------- */
typedef enum
{
	GREEN,
	YELLOW,
	RED	
}TrafficLightState_t;

/* ------------------------------- Global Variables ------------------------------- */
static TrafficLightState_t CarLightState = RED;
static uint8_t flag= 0;
volatile uint8_t btn_state= 0;

seg_t my_seg={
	.seg_mode= SEG_COM_ANODE,
	.seg_pins[0]._port= PORTC_INDEX,
	.seg_pins[0]._pin= PIN0,
	.seg_pins[1]._port= PORTC_INDEX,
	.seg_pins[1]._pin= PIN1,
	.seg_pins[2]._port= PORTC_INDEX,
	.seg_pins[2]._pin= PIN2,
	.seg_pins[3]._port= PORTC_INDEX,
	.seg_pins[3]._pin= PIN3,
	.seg_pins[4]._port= PORTC_INDEX,
	.seg_pins[4]._pin= PIN4,
	.seg_pins[5]._port= PORTC_INDEX,
	.seg_pins[5]._pin= PIN5,
	.seg_pins[6]._port= PORTC_INDEX,
	.seg_pins[6]._pin= PIN6,
	.seg_pins[7]._port= PORTC_INDEX,
	.seg_pins[7]._pin= PIN7,
};

Timer0_cfg_t mytimer={
	.Timer0_mode= TIMER0_MODE_NORMAL,
	.Timer0_Preloaded_Value= 6,
	.Timer0_PreScaler= TIMER0_CLOCK_PRESCALER_1,
	.COV= 2000
};

Spicfg_t My_SPI={
	.spi_mode= SPI_MODE_MASTER,
	.spi_clock_rate= SPI_CLOCKRATE_DIV_16
};


int main(void)
{
	sint8_t counter= 0;
	
	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_RISING_EDGE, EXT0_Handler);
	Timer0_Init(&mytimer);
	SPI_Init(&My_SPI);
	
	/* Initialize External Hardware Devices */
    HAL_Init();

    while(1)
    {	
		/*  ---------------------------- Car Traffic Light is in Red State ---------------------------- */
		CarLightState= GREEN; // CAR_LED_GREEN IS ON
		flag= 0;
		SPI_Transmit(&My_SPI, 'g');
		led_turn_on(PED_RED_PORT, PED_RED_PIN);
		led_turn_on(CAR_GREEN_PORT, CAR_GREEN_PIN);
		
		for(counter = 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			Timer0_WaitBlocking(&mytimer);
			if(flag == 1)
			{
				break;
			}
		}
		led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
		
		/*  ---------------------------- Car Traffic Light is in Yellow State ---------------------------- */
		CarLightState= YELLOW; // CAR_LED_YELLOW IS ON
		flag= 0;
		SPI_Transmit(&My_SPI, 'y');
		for(counter = 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			
			led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			Timer0_WaitBlocking(&mytimer);
			if(flag == 1)
			{
				break;
			}
		}
		led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_off(PED_RED_PORT, PED_RED_PIN);
		
		/*  ---------------------------- Car Traffic Light is in Green State ---------------------------- */
		CarLightState= RED; // CAR_LED_RED IS ON
		flag= 0;
		SPI_Transmit(&My_SPI, 'r');
		led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
		led_turn_on(CAR_RED_PORT, CAR_RED_PIN);
		for(counter = 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			
			Timer0_WaitBlocking(&mytimer);
			if(flag == 1)
			{
				break;
			}
		}
		led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
		
		/*  ---------------------------- Car Traffic Light is in Yellow State ---------------------------- */
		CarLightState= YELLOW; // CAR_LED_YELLOW IS ON
		flag= 0;
		SPI_Transmit(&My_SPI, 'y');
		for(counter = 9; counter >= 0; counter--)
		{
			seg_write_nnum(&my_seg, counter);
			
			led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			Timer0_WaitBlocking(&mytimer);
			if(flag == 1)
			{
				break;
			}
		}
		led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
		led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
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
	sint8_t counter= 0;
	if(btn_state == 0)
	{
		btn_state= 1;
		switch(CarLightState)
		{
			case GREEN:		// Button was pressed when Cars Green Led was on
			SPI_Transmit(&My_SPI, 'g');
			led_turn_off(CAR_GREEN_PORT, CAR_GREEN_PIN);
			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);

			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_on(CAR_RED_PORT, CAR_RED_PIN);
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_RED_PORT, CAR_RED_PIN);

			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
			led_turn_on(PED_RED_PORT, PED_RED_PIN);
			break;
			
			case YELLOW:	// Button was pressed when car_led_yellow was on
			SPI_Transmit(&My_SPI, 'y');
			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);

			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_on(CAR_RED_PORT, CAR_RED_PIN);
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
			
			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_on(CAR_RED_PORT, CAR_RED_PIN);

			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
				Timer0_WaitBlocking(&mytimer);
			}
			//led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_off(PED_GREEN_PORT, PED_GREEN_PIN);
			break;
			
			case RED:		// Button was pressed when car_led_red was on
			SPI_Transmit(&My_SPI, 'r');
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_RED_PORT, CAR_RED_PIN);
			led_turn_off(PED_RED_PORT, PED_RED_PIN);

			for(counter = 9; counter >= 0; counter--)
			{
				seg_write_nnum(&my_seg, counter);
				
				led_toggle(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
				led_toggle(PED_YELLOW_PORT, PED_YELLOW_PIN);
				Timer0_WaitBlocking(&mytimer);
			}
			led_turn_off(CAR_YELLOW_PORT, CAR_YELLOW_PIN);
			led_turn_off(PED_YELLOW_PORT, PED_YELLOW_PIN);
			led_turn_off(PED_RED_PORT, PED_RED_PIN);
			led_turn_on(PED_GREEN_PORT, PED_GREEN_PIN);
			break;
		}
	}
	btn_state= 0;
	flag= 1;
}