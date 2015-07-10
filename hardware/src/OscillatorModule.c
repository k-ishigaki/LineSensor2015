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
// OscillatorModule_ClockSource
// -----------------------------------------------------------------------------
static enum OscillatorModule_ClockSource_Constants {
	INTERNAL_OSCILLATOR_BLOCK,
	TIMER1_OSCILLATOR,
	CLOCK_DETERMINED_BY_FOSC,
};

static const struct OscillatorModule_ClockSource clockSource = {
	INTERNAL_OSCILLATOR_BLOCK,
	TIMER1_OSCILLATOR,
	CLOCK_DETERMINED_BY_FOSC,
};

// -----------------------------------------------------------------------------
// OscillatorModule
// -----------------------------------------------------------------------------
static void OscillatorModule_selectSystemClock(int clockSource) {
	switch((enum OscillatorModule_ClockSource_Constants)clockSource) {
		case INTERNAL_OSCILLATOR_BLOCK:
			OSCCONbits.SCS = 0b10;
			break;
		case TIMER1_OSCILLATOR:
			OSCCONbits.SCS = 0b01;
			break;
		case CLOCK_DETERMINED_BY_FOSC:
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

static const struct OscillatorModule_ClockSource* OscillatorModule_getClockSource() {
	return &clockSource;
}

static OscillatorModule oscillatorModule = {
	OscillatorModule_selectSystemClock,
	OscillatorModule_getInternalOscillator,
	OscillatorModule_getPhaseLockedLoop,
	OscillatorModule_getClockSource,
};

OscillatorModule* getOscillatorModule() {
	return &oscillatorModule;
}

