#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include "std_types.h"
#include "Bit_Masking.h"

#define SFIOR				(*(volatile uint8_t*)0x50)

/* ----------------------- GPIO Registers ----------------------- */
// PORTA
#define GPIO_PORTA			(*(volatile uint8_t*)0x3B)			   		// The Port A Data Register
#define GPIO_DDRA			(*(volatile uint8_t*)0x3A)			  	 	// The Port A Direction Register
#define GPIO_PINA			(*(volatile uint8_t*)0x39)			   		// The Port A Input Pins Address
// PORTB
#define GPIO_PORTB			(*(volatile uint8_t*)0x38)			   		// The Port B Data Register
#define GPIO_DDRB			(*(volatile uint8_t*)0x37)			  	 	// The Port B Direction Register
#define GPIO_PINB			(*(volatile uint8_t*)0x36)			   		// The Port B Input Pins Address
// PORTC
#define GPIO_PORTC			(*(volatile uint8_t*)0x35)			   		// The Port C Data Register
#define GPIO_DDRC			(*(volatile uint8_t*)0x34)			   		// The Port C Direction Register
#define GPIO_PINC			(*(volatile uint8_t*)0x33)			   		// The Port C Input Pins Address
// PORTD
#define GPIO_PORTD			(*(volatile uint8_t*)0x32)			   		// The Port D Data Register
#define GPIO_DDRD			(*(volatile uint8_t*)0x31)			   		// The Port D Direction Register
#define GPIO_PIND			(*(volatile uint8_t*)0x30)			   		// The Port D Input Pins Address

#endif
