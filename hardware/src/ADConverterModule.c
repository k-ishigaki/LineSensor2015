#include "Hardware.h"
#include <xc.h>

// ----------------------------------------------------------------------------
// ADConverterModule_PositiveReference
// ----------------------------------------------------------------------------
enum ADConverterModule_PositiveReference_Constants {
	FVR       = 0b11,
	VREF_PLUS = 0b10,
	VDD       = 0b00,
};

const struct ADConverterModule_PositiveReference 
ADConverterModule_PositiveReference = {
	FVR,
	VREF_PLUS,
	VDD,
};

// ----------------------------------------------------------------------------
// ADConverterModule_NegativeReference
// ----------------------------------------------------------------------------
enum ADConverterModule_NegativeReference_Constants {
	VREF_MINUS = 0b1,
	VSS        = 0b0,
};

const struct ADConverterModule_NegativeReference
ADConverterModule_NegativeReference = {
	VREF_MINUS,
	VSS,
};

// ----------------------------------------------------------------------------
// ADConverterModule_ConversionClock
// ----------------------------------------------------------------------------
enum ADConverterModule_ConversionClock_Constants {
	F_RC         = 0b011,
	F_OSC_DIV_64 = 0b110,
	F_OSC_DIV_32 = 0b010,
	F_OSC_DIV_16 = 0b101,
	F_OSC_DIV_8  = 0b001,
	F_OSC_DIV_4  = 0b100,
	F_OSC_DIV_2  = 0b000,
};

const struct ADConverterModule_ConversionClock
ADConverterModule_ConversionClock = {
	F_RC,
	F_OSC_DIV_64,
	F_OSC_DIV_32,
	F_OSC_DIV_16,
	F_OSC_DIV_8,
	F_OSC_DIV_4,
	F_OSC_DIV_2,
};

// ----------------------------------------------------------------------------
// ADConverterModule_InputChannel
// ----------------------------------------------------------------------------
enum ADConverterModule_InputChannel_Constants {
	FVR_BUFFER_1          = 0b11111,
	DAC                   = 0b11110,
	TEMPERATURE_INDICATOR = 0b11101,
	AN13                  = 0b01101,
	AN12                  = 0b01100,
	AN11                  = 0b01011,
	AN10                  = 0b01010,
	AN9                   = 0b01001,
	AN8                   = 0b01000,
	AN4                   = 0b00100,
	AN3                   = 0b00011,
	AN2                   = 0b00010,
	AN1                   = 0b00001,
	AN0                   = 0b00000,
};

const struct ADConverterModule_InputChannel ADConverterModule_InputChannel = {
	FVR_BUFFER_1,
	DAC,
	TEMPERATURE_INDICATOR,
	AN13,
	AN12,
	AN11,
	AN10,
	AN9,
	AN8,
	AN4,
	AN3,
	AN2,
	AN1,
	AN0,
};

// ----------------------------------------------------------------------------
// ADConverterModule
// ----------------------------------------------------------------------------
static char ADConverterModule_getResolution() {
	return 10;
}

static void ADConverterModule_selectPositiveReference(char ref) {
	ADCON1bits.ADPREF = ref;
}

static void ADConverterModule_selectNegativeReference(char ref) {
	ADCON1bits.ADNREF = ref;
}

static void ADConverterModule_selectConversionClock(char clock) {
	ADCON1bits.ADCS = clock;
}

static void ADConverterModule_selectInputChannel(char channel) {
	ADCON0bits.CHS = channel;
}

static void ADConverterModule_enable() {
	ADCON0bits.ADON = 1;
}

static void ADConverterModule_disable() {
	ADCON0bits.ADON = 0;
}

static void ADConverterModule_startConversion() {
	while(ADCON0bits.GO);
	ADCON0bits.GO = 1;
}

static bool ADConverterModule_isConverting() {
	return ADCON0bits.GO;
}

static unsigned long ADConverterModule_getResult() {
	return ((unsigned int)ADRESH << 2) + (ADRESL >> 6);
}

const ADConverterModule ADConverterModule_instance = {
	ADConverterModule_getResolution,
	ADConverterModule_selectPositiveReference,
	ADConverterModule_selectNegativeReference,
	ADConverterModule_selectConversionClock,
	ADConverterModule_selectInputChannel,
	ADConverterModule_enable,
	ADConverterModule_disable,
	ADConverterModule_startConversion,
	ADConverterModule_isConverting,
	ADConverterModule_getResult,
};

