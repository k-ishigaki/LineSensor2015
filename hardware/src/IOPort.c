#include "Hardware.h"
#include <xc.h>

#ifndef IO_PORT_COMMON_DECRARED
#define IO_PORT_COMMON_DECRARED
// ----------------------------------------------------------------------------
// IOPort_PinMode
// ----------------------------------------------------------------------------
enum IOPort_PinMode_Constants {
	DIGITAL_INPUT,
	DIGITAL_INPUT_WITH_INTERNAL_PULLUP,
	DIGITAL_OUTPUT,
	ANALOG_INPUT,
};

const struct IOPort_PinMode IOPort_PinMode = {
	DIGITAL_INPUT,
	DIGITAL_INPUT_WITH_INTERNAL_PULLUP,
	DIGITAL_OUTPUT,
	ANALOG_INPUT,
};

#endif

// ----------------------------------------------------------------------------
// Port A, Port B, Port C
// ----------------------------------------------------------------------------
#if !defined(PORTA_DECLARED)
#define PORTA_DECLARED

#define Portx_(name) PortA_##name
#define PORTx        PORTA
#define ANSELx       ANSELA
#define TRISx        TRISA
#define LATx         LATA

#elif !defined(PORTB_DECLARED)
#define PORTB_DECLARED

#define Portx_(name) PortB_##name
#define PORTx        PORTB
#define ANSELx       ANSELB
#define TRISx        TRISB
#define LATx         LATB
#define WPUx         WPUB

#elif !defined(PORTC_DECLARED)
#define PORTC_DECLARED

#define Portx_(name) PortC_##name
#define PORTx        PORTC
#define TRISx        TRISC
#define LATx         LATC

#define EXIT_LOOP
#endif

static void Portx_(setPinModes)(uint8_t bits, char mode) {
	switch((enum IOPort_PinMode_Constants)mode) {
		case DIGITAL_INPUT:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
#ifdef WPUx
			WPUx   &= ~bits;
#endif
			TRISx  |= bits;
			break;
		case DIGITAL_INPUT_WITH_INTERNAL_PULLUP:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
#ifdef WPUx
			WPUx   |= bits;
#endif
			TRISx  |= bits;
			break;
		case DIGITAL_OUTPUT:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
			TRISx  &= ~bits;
			break;
		case ANALOG_INPUT:
#ifdef ANSELx
			ANSELx |= bits;
			TRISx  |= bits;
#endif
			break;
	}
}

static uint8_t Portx_(readDigital)() {
	return PORTx;
}

static void Portx_(writeDigital)(uint8_t bits) {
	LATx = bits;
}

const IOPort Portx_(instance) = {
	Portx_(setPinModes),
	Portx_(readDigital),
	Portx_(writeDigital),
};

#undef Portx_
#undef PORTx
#undef ANSELx
#undef TRISx
#undef LATx
#undef WPUx

#if !defined(EXIT_LOOP)
#include "IOPort.c"
#endif
