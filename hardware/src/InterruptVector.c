/*
 * To increase registerable number of interrupts,
 * you can increase LIST_SIZE constant.
 */
#include "Hardware.h"
#include <xc.h>

// dummy instances, priority constants, interrupt vector
// are declared once.
#ifndef DECRARING_INTERRUPT_SERVICE_COMMON
#define DECRARING_INTERRUPT_SERVICE_COMMON

enum {
	LIST_SIZE = 8,
};

// ----------------------------------------------------------------------------
// dummy instances
// ----------------------------------------------------------------------------
static void handler_dummy() {
	// do nothing
}

static void InterruptListener_onInterrupt() {
	// do nothing
}

static InterruptListener listener_dummy = {
	InterruptListener_onInterrupt,
};

// ----------------------------------------------------------------------------
// InterruptService_Priority
// ----------------------------------------------------------------------------
enum InterruptService_Priority_Constants {
	DEFAULT,
};

const struct InterruptService_Priority InterruptService_Priority = {
	DEFAULT,
};

// ----------------------------------------------------------------------------
// InterruptVector
// ----------------------------------------------------------------------------
/** interrupt handlers */
static void (*handlers[LIST_SIZE])() = {&handler_dummy};

/** number of registered handlers */
static unsigned char numOfHandlers = 0;

/** hardware interrupt service routine (ISR) */
static void __interrupt isr() {
	for(unsigned char i = 0; i < numOfHandlers; i++) {
		handlers[i]();
	}
}

/** register handler (void function pointer) to interrupt vector */
static void registerHandler(void (*handler)(), char priority) {
	// If argument handler has been already registered to vector;
	// remove it and register again.
	for(unsigned char i = 0; i < numOfHandlers; i++) {
		if(handlers[i] == handler) {
			numOfHandlers--;
		}
	}
	handlers[numOfHandlers] = handler;
	numOfHandlers++;
}

#endif /* DECRARING_INTERRUPT_SERVICE_COMMON */

// ----------------------------------------------------------------------------
// InterruptService
// ----------------------------------------------------------------------------
#if !defined(AD_CONVERTER_MODULE_INTERRUPT_SERVICE_DECLARED)
#define AD_CONVERTER_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) ADConverterModuleInterruptService_##name
#define PIRbit PIR1bits.ADIF
#define PIEbit PIE1bits.ADIE

#elif !defined(TIMER0_MODULE_INTERRUPT_SERVICE_DECLARED)
#define TIMER0_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) Timer0ModuleInterruptService_##name
#define PIRbit INTCONbits.TMR0IF
#define PIEbit INTCONbits.TMR0IE

#elif !defined(TIMER1_MODULE_INTERRUPT_SERVICE_DECLARED)
#define TIMER1_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) Timer1ModuleInterruptService_##name
#define PIRbit PIR1bits.TMR1IF
#define PIEbit PIE1bits.TMR1IE

#elif !defined(TIMER2_MODULE_INTERRUPT_SERVICE_DECLARED)
#define TIMER2_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) Timer2ModuleInterruptService_##name
#define PIRbit PIR1bits.TMR2IF
#define PIEbit PIE1bits.TMR2IE

#elif !defined(TIMER4_MODULE_INTERRUPT_SERVICE_DECLARED)
#define TIMER4_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) Timer4ModuleInterruptService_##name
#define PIRbit PIR3bits.TMR4IF
#define PIEbit PIE3bits.TMR4IE

#elif !defined(TIMER6_MODULE_INTERRUPT_SERVICE_DECLARED)
#define TIMER6_MODULE_INTERRUPT_SERVICE_DECLARED

#define InterruptService_(name) Timer6ModuleInterruptService_##name
#define PIRbit PIR3bits.TMR6IF
#define PIEbit PIE3bits.TMR6IE

#define EXIT_LOOP
#endif /* AD_CONVERTER_MODULE_INTERRUPT_SERVICE_DECLARED */

static InterruptListener* InterruptService_(listener) = &listener_dummy;

static void InterruptService_(handleInterrupt)() {
	if(PIRbit && PIEbit) {
		InterruptService_(listener)->onInterrupt();
		PIRbit = 0;
	}
}

static void InterruptService_(registerListener)(
		InterruptListener* listener,
		char priority) {
	InterruptService_(listener) = listener;
	registerHandler(&InterruptService_(handleInterrupt), priority);
	// priority is not determined (enhanced mid-range)
}

static void InterruptService_(enableInterrupt)() {
	PIRbit = 0;
	PIEbit = 1;
}

static void InterruptService_(disableInterrupt)() {
	PIEbit = 0;
	PIRbit = 0;
}

const InterruptService InterruptService_(instance) = {
	InterruptService_(registerListener),
	InterruptService_(enableInterrupt),
	InterruptService_(disableInterrupt),
};

#undef InterruptService_
#undef PIRbit
#undef PIEbit

#ifndef EXIT_LOOP
#include "InterruptVector.c"
#endif /* EXIT_LOOP */
