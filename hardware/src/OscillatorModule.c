#include "Hardware.h"
#include <xc.h>

// -----------------------------------------------------------------------------
// InternalOscillator
// -----------------------------------------------------------------------------
static void InternalOscillator_setFrequency(unsigned long frequency) {
	switch (frequency) {
		case 16000000L:
			OSCCONbits.IRCF = 0b1111;
			break;
		case 8000000L:
			OSCCONbits.IRCF = 0b1110;
			break;
		case 4000000L:
			OSCCONbits.IRCF = 0b1101;
			break;
		case 2000000L:
			OSCCONbits.IRCF = 0b1100;
			break;
		case 1000000L:
			OSCCONbits.IRCF = 0b1011;
			break;
		case 500000L:
			OSCCONbits.IRCF = 0b1010;
			break;
		case 250000L:
			OSCCONbits.IRCF = 0b1001;
			break;
		case 62500L:
			OSCCONbits.IRCF = 0b0100;
			break;
		case 31250L:
			OSCCONbits.IRCF = 0b0011;
			break;
		case 31000L:
			OSCCONbits.IRCF = 0b0000;
			break;
	}
}

static InternalOscillator internalOscillator = {
	InternalOscillator_setFrequency,
};

// -----------------------------------------------------------------------------
// PhaseLockedLoop
// -----------------------------------------------------------------------------
static void PhaseLockedLoop_enablePLL() {
	OSCCONbits.SPLLEN = 1;
}

static void PhaseLockedLoop_disablePLL() {
	OSCCONbits.SPLLEN = 0;
}


static PhaseLockedLoop phaseLockedLoop = {
	PhaseLockedLoop_enablePLL,
	PhaseLockedLoop_disablePLL,
};

// -----------------------------------------------------------------------------
// OscillatorModule
// -----------------------------------------------------------------------------
static void OscillatorModule_selectSystemClock(int clockSource) {
	switch((OscillatorModule_ClockSource)clockSource) {
		case OscillatorModule_ClockSource_INTERNAL_OSCILLATOR_BLOCK:
			OSCCONbits.SCS = 0b10;
			break;
		case OscillatorModule_ClockSource_TIMER1_OSCILLATOR:
			OSCCONbits.SCS = 0b01;
			break;
		case OscillatorModule_ClockSource_CLOCK_DETERMINED_BY_FOSC:
			OSCCONbits.SCS = 0b00;
			break;
	}
}

static InternalOscillator* OscillatorModule_getInternalOscillator() {
	return &internalOscillator;
}

static PhaseLockedLoop* OscillatorModule_getPhaseLockedLoop() {
	return &phaseLockedLoop;
}

static OscillatorModule oscillatorModule = {
	OscillatorModule_selectSystemClock,
	OscillatorModule_getInternalOscillator,
	OscillatorModule_getPhaseLockedLoop,
};

OscillatorModule* getOscillatorModule() {
	return &oscillatorModule;
}

