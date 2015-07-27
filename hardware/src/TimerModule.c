#include "Hardware.h"
#include <xc.h>
#include <stddef.h>

#ifndef DECLARED_ONCE
#define DECLARED_ONCE
// ----------------------------------------------------------------------------
// Timer0Module_Constants
// ----------------------------------------------------------------------------
enum Timer0Module_ClockSource_Constants {
	T0_T0CKI,
	T0_CPSCLK,
	T0_F_OSC_DIV_4,
};
const struct Timer0Module_ClockSource Timer0Module_ClockSource = {
	T0_T0CKI,
	T0_CPSCLK,
	T0_F_OSC_DIV_4,
};

enum Timer0Module_Prescaler_Constants {
	T0_RATE_1_1,
	T0_RATE_1_2   = 0b000,
	T0_RATE_1_4   = 0b001,
	T0_RATE_1_8   = 0b010,
	T0_RATE_1_16  = 0b011,
	T0_RATE_1_32  = 0b100,
	T0_RATE_1_64  = 0b101,
	T0_RATE_1_128 = 0b110,
	T0_RATE_1_256 = 0b111,
};
const struct Timer0Module_Prescaler Timer0Module_Prescaler = {
	T0_RATE_1_1,
	T0_RATE_1_2,
	T0_RATE_1_4,
	T0_RATE_1_8,
	T0_RATE_1_16,
	T0_RATE_1_32,
	T0_RATE_1_64,
	T0_RATE_1_128,
	T0_RATE_1_256,
};

// ----------------------------------------------------------------------------
// Timer0Module
// ----------------------------------------------------------------------------
static timer_module_counter_max_t Timer0Module_getCount() {
	return TMR0;
}

static void Timer0Module_setCount(timer_module_counter_max_t count) {
	// note:
	// When TMR0 is written, the increment is inhibited for
	// two instruction cycles immediately following the write
	TMR0 = count;
}

static void Timer0Module_enable() {
	// timer1 module is always enabled
}

static void Timer0Module_disable() {
	// timer1 module is always enabled
}

static void Timer0Module_selectClockSource(char clockSource) {
	switch((enum Timer0Module_ClockSource_Constants)clockSource) {
		case T0_T0CKI:
			OPTION_REGbits.TMR0CS = 1;
			CPSCON0bits.T0XCS     = 0;
			break;
		case T0_CPSCLK:
			OPTION_REGbits.TMR0CS = 1;
			CPSCON0bits.T0XCS     = 1;
			break;
		case T0_F_OSC_DIV_4:
			OPTION_REGbits.TMR0CS = 0;
			CPSCON0bits.T0XCS     = 0;
			break;
	}
}

static void Timer0Module_selectPrescaler(char prescaler) {
	if(prescaler == T0_RATE_1_1) {
		OPTION_REGbits.PSA = 1;
	} else {
		OPTION_REGbits.PSA = 0;
		OPTION_REGbits.PS  = prescaler;
	}
}

static void Timer0Module_selectPostScaler(char postscaler) {
	// postscaler value is always 1:1
}

static void Timer0Module_selectMode(char mode) {
	// if clock source is Fosc, operation is timer mode
	// otherwise it is counter mode
}

static void Timer0Module_setPeriodCount(timer_module_counter_max_t period) {
	// period count is fixed to 255 and not changeable
}

const TimerModule Timer0Module_instance = {
	Timer0Module_getCount,
	Timer0Module_setCount,
	Timer0Module_enable,
	Timer0Module_disable,
	Timer0Module_selectClockSource,
	Timer0Module_selectPrescaler,
	Timer0Module_selectPostScaler,
	Timer0Module_selectMode,
	Timer0Module_setPeriodCount,
	NULL, // does not have gate control
};

// ----------------------------------------------------------------------------
// Timer1GateControl_Constants
// ----------------------------------------------------------------------------
enum Timer1GateControl_Source_Constants {
	T1G_T1G             = 0b00,
	T1G_TIMER0_OVERFLOW = 0b01,
	T1G_SYNC_C1OUT      = 0b10,
	T1G_SYNC_C2OUT      = 0b11,
};
const struct Timer1GateControl_Source Timer1GateControl_Source = {
	T1G_T1G,
	T1G_TIMER0_OVERFLOW,
	T1G_SYNC_C1OUT,
	T1G_SYNC_C2OUT,
};

enum Timer1GateControl_Mode_Constants {
	ENABLE_POSITIVE                  = 0b100,
	ENABLE_NEGATIVE                  = 0b000,
	TOGGLE_POSITIVE                  = 0b110,
	TOGGLE_NEGATIVE                  = 0b010,
	SINGLE_PULSE_POSITIVE            = 0b101,
	SINGLE_PULSE_NEGATIVE            = 0b001,
	TOGGLE_AND_SINGLE_PULSE_POSITIVE = 0b111,
	TOGGLE_AND_SINGLE_PULSE_NEGATIVE = 0b011,
};
const struct Timer1GateControl_Mode Timer1GateControl = {
	ENABLE_POSITIVE,
	ENABLE_NEGATIVE,
	TOGGLE_POSITIVE,
	TOGGLE_NEGATIVE,
	SINGLE_PULSE_POSITIVE,
	SINGLE_PULSE_NEGATIVE,
	TOGGLE_AND_SINGLE_PULSE_POSITIVE,
	TOGGLE_AND_SINGLE_PULSE_NEGATIVE,
};

// ----------------------------------------------------------------------------
// Timer1GateControl
// ----------------------------------------------------------------------------
static void Timer1GateControl_selectSource(char source) {
	T1GCONbits.T1GSS = source;
}

static void Timer1GateControl_selectMode(char mode) {
	T1GCONbits.T1GPOL = mode >> 2;
	T1GCONbits.T1GTM  = mode >> 1;
	T1GCONbits.T1GSPM = mode;
}

static bool Timer1GateControl_getState() {
	return T1GCONbits.T1GVAL;
}

static void Timer1GateControl_startSinglePulseAquisition() {
	T1GCONbits.T1GGO = 1;
}

static bool Timer1GateControl_isWaitingSinglePulse() {
	return T1GCONbits.T1GGO;
}

const TimerGateControl Timer1GateControl_instance = {
	Timer1GateControl_selectSource,
	Timer1GateControl_selectMode,
	Timer1GateControl_getState,
	Timer1GateControl_startSinglePulseAquisition,
	Timer1GateControl_isWaitingSinglePulse,
};

// ----------------------------------------------------------------------------
// Timer1Module_Constants
// ----------------------------------------------------------------------------
enum Timer1Module_ClockSource_Constants {
	T1_T1OSC_SYNC      = 0b0110,
	T1_T1OSC_NOT_SYNC  = 0b1110,
	T1_CPSCLK_SYNC     = 0b0011,
	T1_CPSCLK_NOT_SYNC = 0b1011,
	T1_T1CKI_SYNC      = 0b0010,
	T1_T1CKI_NOT_SYNC  = 0b1010,
	T1_F_OSC           = 0b0001,
	T1_F_OSC_DIV_4     = 0b0000,
};
const struct Timer1Module_ClockSource Timer1Module_ClockSource = {
	T1_T1OSC_SYNC,
	T1_T1OSC_NOT_SYNC,
	T1_CPSCLK_SYNC,
	T1_CPSCLK_NOT_SYNC,
	T1_T1CKI_SYNC,
	T1_T1CKI_NOT_SYNC,
	T1_F_OSC,
	T1_F_OSC_DIV_4,
};

enum Timer1Module_Prescaler_Constants {
	T1_RATE_1_1 = 0b00,
	T1_RATE_1_2 = 0b01,
	T1_RATE_1_4 = 0b10,
	T1_RATE_1_8 = 0b11,
};
const struct Timer1Module_Prescaler Timer1Module_Prescaler = {
	T1_RATE_1_1,
	T1_RATE_1_2,
	T1_RATE_1_4,
	T1_RATE_1_8,
};

enum Timer1Module_Mode_Constants {
	T1_ALWAYS_COUNT = 0,
	T1_GATE_COUNT   = 1,
};
const struct Timer1Module_Mode Timer1Module_Mode = {
	T1_ALWAYS_COUNT,
	T1_GATE_COUNT,
};

// ----------------------------------------------------------------------------
// Timer1Module
// ----------------------------------------------------------------------------
static timer_module_counter_max_t Timer1Module_getCount() {
	// 16bit read/write mode is not available (pic16f)
	// so it is recommended to stop timer before read count
	return ((timer_module_counter_max_t)TMR1H << 8) + TMR1L;
}

static void Timer1Module_setCount(timer_module_counter_max_t count) {
	// 16bit read/write mode is not available (pic16f)
	// so it is recommended to stop timer before write count
	TMR1H = count >> 8;
	TMR1L = count;
}

static void Timer1Module_enable() {
	T1CONbits.TMR1ON = 1;
}

static void Timer1Module_disable() {
	T1CONbits.TMR1ON = 0;
}

static void Timer1Module_selectClockSource(char clockSource) {
	T1CONbits.TMR1CS  = clockSource;
	T1CONbits.T1OSCEN = clockSource >> 2;
	T1CONbits.nT1SYNC = clockSource >> 3;
}

static void Timer1Module_selectPrescaler(char prescaler) {
	T1CONbits.T1CKPS = prescaler;
}

static void Timer1Module_selectPostscaler(char postscaler) {
	// postscaler is fixed to 1:1
}

static void Timer1Module_selectMode(char mode) {
	T1GCONbits.TMR1GE = mode;
}

static void Timer1Module_setPeriodCount(timer_module_counter_max_t count) {
	// period count is fixed to 65535 and not changeable
}

const TimerModule Timer1Module_instance = {
	Timer1Module_getCount,
	Timer1Module_setCount,
	Timer1Module_enable,
	Timer1Module_disable,
	Timer1Module_selectClockSource,
	Timer1Module_selectPrescaler,
	Timer1Module_selectPostscaler,
	Timer1Module_selectMode,
	Timer1Module_setPeriodCount,
	&Timer1GateControl_instance,
};

#endif

#define EXIT_LOOP


#ifndef EXIT_LOOP
#include "TimerModule.c"
#endif
