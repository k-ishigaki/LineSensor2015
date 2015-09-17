#ifndef CCP_MODULE_H
#define CCP_MODULE_H

#include <stdint.h>

/**
 * Captures pin event and gets timer count value of that time.
 *
 * The got timer count is obtained at Capture#getCapturedCount.
 */
struct Capture {
	/**
	 * Get the captured timer count value/
	 *
	 * If capture event occured when reading captured count,
	 * the value may be uncorrect.
	 */
	uint16_t (*getCapturedCount)(void);
};

/**
 * Compare presetting count value with base timer count value.
 *
 * On compare matched, a event occur.
 * The event may be user settable. (ex: software interrupt)
 */
struct Compare {
	/**
	 * Set count value compared with base timer count.
	 *
	 * The count value range depend on that of base timer.
	 */
	void (*setComparedCount)(uint16_t);
};

/**
 * Configurator of PWM output.
 */
struct PWM {
	/**
	 * Set duty cycle count.
	 *
	 * @param duty cycle count
	 */
	void (*setDutyCycle)(uint16_t);
};

#endif
