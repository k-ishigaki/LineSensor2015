/*
 * InterruptVector.c
 * declares InterruptVector.
 * To increase registerable number of interrupts,
 * you can increase LIST_SIZE constant.
 */
#include "Hardware.h"
#include <xc.h>

enum {
	LIST_SIZE = 8,
};

// -----------------------------------------------------------------------------
// dummy instances
// -----------------------------------------------------------------------------
static bool InterruptSource_isPending() {
	// always returns false
	return false;
}

static InterruptSource source_dummy = {
	InterruptSource_isPending,
};

static void InterruptListener_onInterrupt() {
	// do nothing
}

static InterruptListener listener_dummy = {
	InterruptListener_onInterrupt,
};

// -----------------------------------------------------------------------------
// InterruptVector_Priority
// -----------------------------------------------------------------------------
enum InterruptVector_Priority_Constants {
	HIGH_PRIORITY,
	LOW_PRIORITY,
};

const struct InterruptVector_Priority InterruptVector_Priority = {
	HIGH_PRIORITY,
	LOW_PRIORITY,
};

// -----------------------------------------------------------------------------
// InterruptVector
// -----------------------------------------------------------------------------
/** interrupt sources (high priority) */
static InterruptSource* sources_H[LIST_SIZE] = {&source_dummy};
/** interrupt sources (low priority) */
static InterruptSource* sources_L[LIST_SIZE] = {&source_dummy};
/** interrupt listeners (high priority) */
static InterruptListener* listeners_H[LIST_SIZE] = {&listener_dummy};
/** interrupt listeners (low priority) */
static InterruptListener* listeners_L[LIST_SIZE] = {&listener_dummy};
/** pointer of lists (high priority) */
static unsigned char pointer_H = 0;
/** pointer of lists (low priority) */
static unsigned char pointer_L = 0;

// hardware interrupt service routine (ISR)
static void __interrupt isr() {
	bool interruptOccurred = false;
	for(unsigned char i = 0; i < pointer_H; i++) {
		if(sources_H[i]->isPending()) {
			listeners_H[i]->onInterrupt();
			interruptOccurred = true;
		}
	}
	// If high priority interrupt occurred, return from interrupt.
	// And then if any interrupts are pending, interrupt again.
	// This is because of distinction between high and low priority.
	if(interruptOccurred) return;
	for(unsigned char i = 0; i < pointer_L; i++) {
		if(sources_L[i]->isPending()) {
			listeners_L[i]->onInterrupt();
			// Once low priority interrupt occurred,
			// return from interrupt to deal with
			// high priority interrupts.
			return;
		}
	}
}

static void InterruptVector_addInterrupt(
		InterruptSource* source,
		InterruptListener* listener,
		int priority) {
	switch((enum InterruptVector_Priority_Constants)priority) {
		case LOW_PRIORITY:
			sources_L[pointer_L] = source;
			listeners_L[pointer_L] = listener;
			pointer_L++;
			break;
		case HIGH_PRIORITY:
			sources_H[pointer_H] = source;
			listeners_H[pointer_H] = listener;
			pointer_H++;
			break;
	}
}

static const InterruptVector interruptVector = {
	InterruptVector_addInterrupt,
};

const InterruptVector* getInterruptVector() {
	return &interruptVector;
}
