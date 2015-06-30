#ifndef HARDWARE_GPIO_PIN_H
#define HARDWARE_GPIO_PIN_H

#include <stdbool.h>

typedef struct {
	/**
	 * Get pin state.
	 * @return pin state high = true, low = false.
	 */
	bool (*getPinState)(void);
} DigitalInputPin;

typedef struct {
	/**
	 * Get pin state (with internal pullup).
	 * @return pin state high = true, low = false.
	 */
	bool (*getPinState)(void);
} DigitalInputPinWithInternalPullup;

typedef struct {
	/**
	 * Get pin state (with internal pulldown).
	 * @return pin state high = true, low = false.
	 */
	bool (*getPinState)(void);
} DigitalInputPinWithInternalPulldown;

typedef struct {
	/**
	 * Set pin state.
	 * @param pin state true = high, false = low.
	 */
	void (*setPinState)(void);
} DigitalOutputPin;

typedef struct {
	/**
	 * Set direction.
	 * @param true = output, false = input.
	 */
	void (*setDirection)(bool);
	/**
	 * Get pin state (with internal pulldown).
	 * Before use this method, {@code setDirection(false)} must
	 * be called.
	 * @return pin state high = true, low = false.
	 */
	bool (*getPinState)(void);
	/**
	 * Set pin state.
	 * Before use this method, {@code setDirection(true)} must
	 * be called.
	 * @param pin state true = high, false = low.
	 */
	void (*setPinState)(bool);
} GPIOPin;

#endif /* HARDWARE_GPIO_PIN_H */
