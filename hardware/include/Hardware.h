/*
 * Hardware.h
 * definitions for PIC16F1938
 */
#ifndef HARDWARE_H
#define HARDWARE_H

// ----------------------------------------------------------------------------
// device configurations
// ----------------------------------------------------------------------------
// CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config CLKOUTEN = OFF
// WDT controlled by the SWDTEN bit in the WDTCON register
#pragma config WDTE = SWDTEN
// PWRT enabled
#pragma config PWRTE = ON
// Program memory code protection is disabled
#pragma config CP = OFF
// Brown-out Reset controlled by the SBOREN bit in the BORCON register
#pragma config BOREN = ON
// Fail-Safe Clock Monitor is enabled
#pragma config FCMEN = ON
// MCLR/VPP pin function is MCLR
#pragma config MCLRE = ON
// Data memory code protection is disabled
#pragma config CPD = OFF
// Internal/External Switchover mode is disabled
#pragma config IESO = OFF
// INTOSC oscillator: I/O function on CLKIN pin
#pragma config FOSC = INTOSC
// Stack Overflow or Underflow will cause a Reset
#pragma config STVREN = ON
// Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config BORV = LO
// Low-voltage programming enabled
#pragma config LVP = ON
// Write protection off
#pragma config WRT = OFF
// 4x PLL enabled
#pragma config PLLEN = ON

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------
#define OPERATING_VOLTAGE   5.0
#define OPERATING_FREQUENCY 32000000L

// ----------------------------------------------------------------------------
// InterruptVector
// ----------------------------------------------------------------------------
#include "InterruptVector.h"

struct InterruptService_Priority {
	/** High priority interrupt */
	char HIGH_PRIORITY;
	/** Low priority interrupt */
	char LOW_PRIORITY;
};

extern const struct InterruptService_Priority InterruptService_Priority;

// ----------------------------------------------------------------------------
// OscillatorModule
// ----------------------------------------------------------------------------
#include "OscillatorModule.h"

struct InternalOscillator_Frequency {
	char HF_16MHz;
	char HF_8MHz;
	char HF_4MHz;
	char HF_2MHz;
	char HF_1MHz;
	char HF_500kHz;
	char HF_250kHz;
	char HF_125kHz;
	char MF_500kHz;
	char MF_250kHz;
	char MF_125kHz;
	char MF_62500Hz;
	char HF_31250Hz;
	char MF_31250Hz;
	char LF_31kHz;
};

extern const struct InternalOscillator_Frequency InternalOscillator_Frequency;

struct OscillatorModule_ClockSource {
	/** Internal oscillator block */
	char INTERNAL;
	/** Secondary (SOSC) oscillator */
	char SECONDARY;
	/** Primary clock (determined by FOSC<3:0> in CONFIG1H)  */
	char DETERMINED_BY_CONFIG;
};

/** defined at OscillatorModule.c */
extern const struct OscillatorModule_ClockSource OscillatorModule_ClockSource;

// ----------------------------------------------------------------------------
// IOPort
// ----------------------------------------------------------------------------
#include "IOPort.h"

struct IOPort_PinMode {
	char DIGITAL_INPUT;
	char DIGITAL_INPUT_WITH_INTERNAL_PULLUP;
	char DIGITAL_OUTPUT;
	char ANALOG_INPUT;
}

/** defined at IOPort.c */
extern const struct IOPort_PinMode IOPort_PinMode;

// ----------------------------------------------------------------------------
// ADConverterModule
// ----------------------------------------------------------------------------
#include "ADConverterModule.h"

struct ADConverterModule_PositiveReference {
	char FVR;
	char VREF_PLUS;
	char VDD;
};

extern const struct ADConverterModule_PositiveReference ADConverterModule_PositiveReference;

struct ADConverterModule_NegativeReference {
	char VREF_MINUS;
	char VSS;
};

extern const struct ADConverterModule_NegativeReference ADConverterModule_NegativeReference;

struct ADConverterModule_ConversionClock {
	char F_RC;
	char F_OSC_DIV_64;
	char F_OSC_DIV_32;
	char F_OSC_DIV_16;
	char F_OSC_DIV_8;
	char F_OSC_DIV_4;
	char F_OSC_DIV_2;
};

extern const struct ADConverterModule_ConversionClock ADConverterModule_ConversionClock;

struct ADConverterModule_InputChannel {
	char FVR_BUFFER_1;
	char DAC;
	char TEMPERATURE_INDICATOR;
	char AN13;
	char AN12;
	char AN11;
	char AN10;
	char AN9;
	char AN8;
	// AN5, AN6, AN7 are not available on the PIC16F1933/1936/1938
	char AN4;
	char AN3;
	char AN2;
	char AN1;
	char AN0;
};

extern const struct ADConverterModule_InputChannel ADConverterModule_InputChannel;

/**
 * Hardware peripheral definition.
 */
struct Hardware {
	const InterruptService* ADConverterModuleInterruptService;
	const OscillatorModule* OscillatorModule;
	const IOPort* PortA;
	const IOPort* PortB;
	const IOPort* PortC;
	const ADConverterModule* ADConverterModule;
};

/**
 * Hardware singleton instance.
 * This is declared at Hardware.c
 */
extern const struct Hardware Hardware;

#endif /* HARDWARE_H */
