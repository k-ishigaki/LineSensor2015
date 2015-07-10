#include "Hardware.h"
#include <xc.h>

// -----------------------------------------------------------------------------
// Port A, Port B, Port C
// -----------------------------------------------------------------------------
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

#elif !defined(PORTC_DECLARED)
#define PORTC_DECLARED

#define Portx_(name) PortC_##name
#define PORTx        PORTC
#define TRISx        TRISC
#define LATx         LATC

#define EXIT_LOOP
#endif

static void Portx_(setAnalogInput)(uint8_t bits) {
#ifdef ANSELx
	ANSELx |= bits;
	TRISx  |= bits;
#endif
}

static void Portx_(setAnalogOutput)(uint8_t bits) {
#ifdef ANSELx
	ANSELx |= bits;
	TRISx  &= ~bits;
#endif
}

static void Portx_(setDigitalInput)(uint8_t bits) {
#ifdef ANSELx
	ANSELx &= ~bits;
#endif
	TRISx  |= bits;
}

static void Portx_(setDigitalOutput)(uint8_t bits) {
#ifdef ANSELx
	ANSELx &= ~bits;
#endif
	TRISx  &= ~bits;
}

static uint8_t Portx_(readDigital)() {
	return PORTx;
}

static void Portx_(writeDigital)(uint8_t bits) {
	LATx = bits;
}

static IOPort Portx_(instance) = {
	Portx_(setAnalogInput),
	Portx_(setAnalogOutput),
	Portx_(setDigitalInput),
	Portx_(setDigitalOutput),
	Portx_(readDigital),
	Portx_(writeDigital),
};

IOPort* Portx_(getInstance)() {
	return &Portx_(instance);
}

#undef Portx_
#undef PORTx
#undef ANSELx
#undef TRISx
#undef LATx

#if !defined(EXIT_LOOP)
#include "IOPort.c"
#endif
