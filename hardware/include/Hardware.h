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
// NativeInterrupts
// ----------------------------------------------------------------------------
#include "NativeInterrupts.h"

struct InterruptService_Priority {
	/** priority is dafault only */
	char DEFAULT;
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

// ----------------------------------------------------------------------------
// TimerModule
// ----------------------------------------------------------------------------
#include "TimerModule.h"

struct Timer0Module_ClockSource {
	/** external T0CKI pin */
	char T0CKI;
	/** capacitive sensing oscillator */
	char CPSCLK;
	/** internal instruction cycle clock */
	char F_OSC_DIV_4;
};
extern const struct Timer0Module_ClockSource Timer0Module_ClockSource;

struct Timer0Module_Prescaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_4;
	char RATE_1_8;
	char RATE_1_16;
	char RATE_1_32;
	char RATE_1_64;
	char RATE_1_128;
	char RATE_1_256;
};
extern const struct Timer0Module_Prescaler Timer0Module_Prescaler;

// timer0 module postscaler is not selectable

struct Timer1Module_ClockSource {
	/**
	 * delicated low-power 32.768kHz oscillator circuit
	 * between pins T1OSI and T1OSO
	 */
	char T1OSC_SYNC;
	/**
	 * delicated low-power 32.768kHz oscillator circuit
	 * (not sync with Fosc)
	 * between pins T1OSI and T1OSO
	 */
	char T1OSC_NOT_SYNC;
	/** capacitive sensing oscillator */
	char CPSCLK_SYNC;
	/** capacitive sensing oscillator (not sync with Fosc) */
	char CPSCLK_NOT_SYNC;
	/** external clock on T1CKI pin */
	char T1CKI_SYNC;
	/** external clock on T1CKI pin (not sync with Fosc) */
	char T1CKI_NOT_SYNC;
	/** system clock */
	char F_OSC;
	/** internal instruction cycle clock */
	char F_OSC_DIV_4;
};
extern const struct Timer1Module_ClockSource Timer1Module_ClockSource;

struct Timer1Module_Prescaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_4;
	char RATE_1_8;
};
extern const struct Timer1Module_Prescaler Timer1Module_Prescaler;

struct Timer1GateControl_Source {
	/** timer1 gate pin */
	char T1G;
	/** overflow of timer0 */
	char TIMER0_OVERFLOW;
	/** comparator1 output */
	char SYNC_C1OUT;
	/** comparator2 output */
	char SYNC_C2OUT;
};
extern const struct Timer1_GateControlSource Timer1_GateControlSource;

struct Timer1GateControl_Mode {
	char ENABLE_POSITIVE;
	char ENABLE_NEGATIVE;
	char TOGGLE_POSITIVE;
	char TOGGLE_NEGATIVE;
	char SINGLE_PULSE_POSITIVE;
	char SINGLE_PULSE_NEGATIVE;
	char TOGGLE_AND_SINGLE_PULSE_POSITIVE;
	char TOGGLE_AND_SINGLE_PULSE_NEGATIVE;
};
extern const struct Timer1GateControl_Mode Timer1GateControl_Mode;

// timer2/4/6 module have only one clock source (Fosc/4)

struct Timer2Module_Prescaler {
	char RATE_1_1;
	char RATE_1_4;
	char RATE_1_16;
	char RATE_1_64;
};
extern const struct Timer2Module_Prescaler Timer2Module_Prescaler;

struct Timer2Module_Postscaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_3;
	char RATE_1_4;
	char RATE_1_5;
	char RATE_1_6;
	char RATE_1_7;
	char RATE_1_8;
	char RATE_1_9;
	char RATE_1_10;
	char RATE_1_11;
	char RATE_1_12;
	char RATE_1_13;
	char RATE_1_14;
	char RATE_1_15;
	char RATE_1_16;
};
extern const struct Timer2Module_Postscaler Timer2Module_Postscaler;

// ----------------------------------------------------------------------------
// CCPModule
// ----------------------------------------------------------------------------
#include "CCPModule.h"

struct CaptureModule_Mode {
	char EVERY_FALLING_EDGE;
	char EVERY_RISING_EDGE;
	char EVERY_4TH_RISING_EDGE;
	char EVERY_16TH_RISING_EDGE;
};
extern const struct CaptureModule_Mode CaptureModule_Mode;

struct CompareModule_Mode {
	/**
	 * initialize ECCPx pin low
	 *
	 * set output on compare match (set CCPxIF)
	 */
	char LOW_TO_HIGH;
	/**
	 * initialize ECCPx pin high
	 *
	 * clear output on compare match (set CCPxIF)
	 */
	char HIGH_TO_LOW;
	/**
	 * generate software interrupt only
	 *
	 * ECCPx pin reverts to I/O state
	 */
	char SOFTWARE_INTERRUPT;
	/**
	 *  Special Event Trigger(not implemented on CCP4 and CCP5)
	 *
	 *  (ECCPx resets Timer, sets CCPxIF bit starts A/D conversion if A/D
	 *  module is enabled)
	 */
	char SPECIAL_EVENT_TRIGGER;
};
extern const struct CompareModule_Mode CompareModule_Mode;

struct PWMModule_BaseTimer {
	char TIMER2;
	char TIMER4;
	char TIMER6;
};
extern const struct PWMModule_BaseTimer PWMModule_BaseTimer;

struct PWMModule_OutputConfig {
	char SINGLE;
	char FULL_BRIDGE_FORWARD;
	char HALF_BRIDGE;
	char FULL_BRIDGE_REVERCE;
};
extern const struct PWMModule_OutputConfig PWMModule_OutputConfig;

struct PWMModule_OutputPolarity {
	/**
	 * PxA, PxC active-high; PxB, PxD active-high
	 */
	char ACTIVE_HIGH_ACTIVE_HIGH;
	/**
	 * PxA, PxC active-high; PxB, PxD active-low
	 */
	char ACTIVE_HIGH_ACTIVE_LOW;
	/**
	 * PxA, PxC active-low; PxB, PxD active-high
	 */
	char ACTIVE_LOW_ACTIVE_HIGH;
	/**
	 * PxA, PxC active-low; PxB, PxD active-low
	 */
	char ACTIVE_LOW_ACTIVE_LOW;
};
extern const struct PWMModule_OutputPolarity PWMModule_OutputPolarity;

/**
 * Hardware peripheral definition.
 */
struct Hardware {
	const InterruptService* ADConverterModuleInterruptService;
	const InterruptService* Timer0ModuleInterruptService;
	const InterruptService* Timer1ModuleInterruptService;
	const InterruptService* Timer1GateControlInterruptService;
	const InterruptService* Timer2ModuleInterruptService;
	const InterruptService* Timer4ModuleInterruptService;
	const InterruptService* Timer6ModuleInterruptService;
	const InterruptService* CCP1ModuleInterruptService;
	const InterruptService* CCP2ModuleInterruptService;
	const InterruptService* CCP3ModuleInterruptService;
	const InterruptService* CCP4ModuleInterruptService;
	const InterruptService* CCP5ModuleInterruptService;
	const OscillatorModule* OscillatorModule;
	const InternalOscillator* InternalOscillator;
	const PhaseLockedLoop* PhaseLockedLoop;
	const IOPort* PortA;
	const IOPort* PortB;
	const IOPort* PortC;
	const ADConverterModule* ADConverterModule;
	const TimerModule* Timer0;
	const TimerModule* Timer1;
	const TimerGateControl* Timer1GateControl;
	const TimerModule* Timer2;
	const TimerModule* Timer4;
	const TimerModule* Timer6;
	const CaptureModule* CaptureModule1;
	const CaptureModule* CaptureModule2;
	const CaptureModule* CaptureModule3;
	const CaptureModule* CaptureModule4;
	const CaptureModule* CaptureModule5;
	const CompareModule* CompareModule1;
	const CompareModule* CompareModule2;
	const CompareModule* CompareModule3;
	const CompareModule* CompareModule4;
	const CompareModule* CompareModule5;
	const PWMModule* PWMModule1;
	const PWMModule* PWMModule2;
	const PWMModule* PWMModule3;
	const PWMModule* PWMModule4;
	const PWMModule* PWMModule5;
};

/**
 * Hardware singleton instance.
 * This is declared at Hardware.c
 */
extern const struct Hardware Hardware;

#endif /* HARDWARE_H */
