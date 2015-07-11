/*
 * InterruptVector.h
 * InterruptVector is singleton instance represents a interrupt vector.
 * Other hardware instances can use the interrupt through
 * {@code interruptVector.addInterrupt(s, l, p)}
 * where these arguments are explained below.
 */
#ifndef INTERRUPT_VECTOR_H
#define INTERRUPT_VECTOR_H

#include <stdbool.h>

typedef struct {
	/**
	 * Return whether interrupt pending or not.
	 * If so, the pair listenr is called.
	 * @return pending = true, not = false
	 */
	bool (const *isPending)(void);
} InterruptSource;

typedef struct {
	/**
	 * Called when interrupt/interrupts is/are pending.
	 * This method must be terminated shortly (about within 10 us)
	 * because it is called at interrupt vector
	 * and other any interrupts cannnot occur.
	 */
	void (const *onInterrupt)(void);
} InterruptListener;

typedef struct {
	/**
	 * Add a interrupt source and the pair listener.
	 * The priority is defined at Hardware.h
	 * @param interrupt source
	 * @param interrupt listener
	 * @param priority
	 */
	void (const *addInterrupt)(InterruptSource*, InterruptListener*, int);
} InterruptVector;

#endif /* INTERRUPT_VECTOR_H */
