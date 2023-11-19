#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include "std_types.h"
#include "Bit_Masking.h"

#define SFIOR				(*(volatile uint8_t*)0x50)

/* ------------------------------------------- GPIO Registers ------------------------------------------- */
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


/* ------------------------------------------- Interrupt Registers ------------------------------------------- */
// The AVR Status Register - SREG
#define SREG				(*(volatile uint8_t*)0x5F)
#define I					7

// MCU Control Register – MCUCR
#define MCUCR				(*(volatile uint8_t*)0x55)
#define ISC00				0
#define ISC01				1
#define ISC10				2
#define ISC11				3
#define SM0					4
#define SM1					5
#define SE					6
#define SM2					7

// MCU Control and Status Register – MCUCSR
#define MCUCSR				(*(volatile uint8_t*)0x54)
#define PORF				0
#define EXTRF				1
#define BORF				2
#define WDRF				3
#define JTRF				4
#define ISC2				6
#define JTD					7

// General Interrupt Control Register – GICR
#define GICR				(*(volatile uint8_t*)0x5B)
#define IVCE				0
#define IVSEL				1
#define INT2				5
#define INT0				6
#define INT1				7

// General Interrupt Flag Register – GIFR
#define GIFR				(*(volatile uint8_t*)0x5A)
#define INTF2				5
#define INTF0				6
#define INTF1				7

#endif
