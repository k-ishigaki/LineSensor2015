#include "Hardware.h"
#include <xc.h>


// ----------------------------------------------------------------------------
// InternalOscillator_Frequency
// ----------------------------------------------------------------------------
enum InternalOscillator_Frequency_Constants {
	HF_16MHz   = 0b1111,
	HF_8MHz    = 0b1110,
	HF_4MHz    = 0b1101,
	HF_2MHz    = 0b1100,
	HF_1MHz    = 0b1011,
	HF_500kHz  = 0b1010,
	HF_250kHz  = 0b1001,
	HF_125kHz  = 0b1000,
	MF_500kHz  = 0b0111,
	MF_250kHz  = 0b0110,
	MF_125kHz  = 0b0101,
	MF_62500Hz = 0b0100,
	HF_31250Hz = 0b0011,
	MF_31250Hz = 0b0010,
	LF_31kHz   = 0b0001,
};

const struct InternalOscillator_Frequency InternalOscillator_Frequency = {
	HF_16MHz,
	HF_8MHz,
	HF_4MHz,
	HF_2MHz,
	HF_1MHz,
	HF_500kHz,
	HF_250kHz,
	HF_125kHz,
	MF_500kHz,
	MF_250kHz,
	MF_125kHz,
	MF_62500Hz,
	HF_31250Hz,
	MF_31250Hz,
	LF_31kHz,
};


// ----------------------------------------------------------------------------
// InternalOscillator
// ----------------------------------------------------------------------------
static void InternalOscillator_selectFrequency(char frequency) {
	OSCCONbits.IRCF = frequency;
}

static const InternalOscillator InternalOscillator_instance = {
	InternalOscillator_selectFrequency,
};

// ----------------------------------------------------------------------------
// PhaseLockedLoop
// ----------------------------------------------------------------------------
static void PhaseLockedLoop_enablePLL() {
	OSCCONbits.SPLLEN = 1;
}

static void PhaseLockedLoop_disablePLL() {
	OSCCONbits.SPLLEN = 0;
}


static const PhaseLockedLoop PhaseLockedLoop_instance = {
	PhaseLockedLoop_enablePLL,
	PhaseLockedLoop_disablePLL,
};

// ----------------------------------------------------------------------------
// OscillatorModule_ClockSource
// ----------------------------------------------------------------------------
enum OscillatorModule_ClockSource_Constants {
	INTERNAL             = 0b10,
	SECONDARY            = 0b01,
	DETERMINED_BY_CONFIG = 0b00,
};

const struct OscillatorModule_ClockSource OscillatorModule_ClockSource = {
	INTERNAL,
	SECONDARY,
	DETERMINED_BY_CONFIG,
};

// ----------------------------------------------------------------------------
// OscillatorModule
// ----------------------------------------------------------------------------
static void OscillatorModule_selectSystemClock(char clockSource) {
	OSCCONbits.SCS = clockSource;
}

const OscillatorModule OscillatorModule_instance = {
	OscillatorModule_selectSystemClock,
	&InternalOscillator_instance,
	&PhaseLockedLoop_instance,
};
