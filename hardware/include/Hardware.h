/*
 * Hardware.h
 * definitions for PIC16F1825
 */
#ifndef HARDWARE_H
#define HARDWARE_H

// -----------------------------------------------------------------------------
// device configurations
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// constants
// -----------------------------------------------------------------------------
#define OPERATING_VOLTAGE   5.0
#define OPERATING_FREQUENCY 32000000L

// -----------------------------------------------------------------------------
// InterruptVector
// -----------------------------------------------------------------------------
#include "InterruptVector.h"

struct InterruptVector_Priority {
	/** High priority interrupt */
	char HIGH_PRIORITY;
	/** Low priority interrupt */
	char LOW_PRIORITY;
};

extern const struct InterruptVector_Priority;

// -----------------------------------------------------------------------------
// OscillatorModule
// -----------------------------------------------------------------------------
#include "OscillatorModule.h"

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

// -----------------------------------------------------------------------------
// IOPort
// -----------------------------------------------------------------------------
#include "IOPort.h"

/**
 * Hardware peripheral definition.
 */
struct Hardware {
	const InterruptVector* InterruptVector;
	const OscillatorModule* OscillatorModule;
	const IOPort* PortA;
	const IOPort* PortB;
	const IOPort* PortC;
};

/**
 * Hardware singleton instance.
 * This is declared at Hardware.c
 */
extern const struct Hardware Hardware;

#endif /* HARDWARE_H */
