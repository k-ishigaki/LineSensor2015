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
	HIGH_PRIORITY,
	LOW_PRIORITY,
};

const struct InterruptService_Priority InterruptService_Priority = {
	HIGH_PRIORITY,
	LOW_PRIORITY,
};

// ----------------------------------------------------------------------------
// InterruptVector
// ----------------------------------------------------------------------------
/** interrupt handlers (high priority) */
static void (*handlers_H[LIST_SIZE])() = {&handler_dummy};

/** interrupt handlers (low priority) */
static void (*handlers_L[LIST_SIZE])() = {&handler_dummy};

/** pointer of lists (high priority) */
static unsigned char pointer_H = 0;

/** pointer of lists (low priority) */
static unsigned char pointer_L = 0;

/** hardware interrupt service routine (ISR) */
static void __interrupt isr() {
	bool interruptOccurred = false;
	for(unsigned char i = 0; i < pointer_H; i++) {
		handlers_H[i]();
		interruptOccurred = true;
	}
	// If high priority interrupt occurred, return from interrupt.
	// And then if any interrupts are pending, interrupt again.
	// This is because of distinction between high and low priority.
	if(interruptOccurred) return;
	for(unsigned char i = 0; i < pointer_L; i++) {
		handlers_L[i]();
		// Once low priority interrupt occurred,
		// return from interrupt to deal with
		// high priority interrupts.
		return;
	}
}

/** register handler (void function pointer) to interrupt vector */
static void registerHandler(void (*handler)(), char priority) {
	// If argument handler has been already registered to vector;
	// remove it and register again.
	for(unsigned char i = 0; i < pointer_L; i++) {
		if(handlers_L[i] == handler) {
			pointer_L--;
		}
	}
	for(unsigned char i = 0; i < pointer_H; i++) {
		if(handlers_H[i] == handler) {
			pointer_H--;
		}
	}
	switch((enum InterruptService_Priority_Constants)priority) {
		case LOW_PRIORITY:
			handlers_L[pointer_L] = handler;
			pointer_L++;
			break;
		case HIGH_PRIORITY:
			handlers_H[pointer_H] = handler;
			pointer_H++;
			break;
	}
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
#include "InterruptVector.h"
#endif /* EXIT_LOOP */
