#ifndef CCP_MODULE_H
#define CCP_MODULE_H

#include <stdint.h>

/**
 * Captures pin event and gets timer count value of that time.
 *
 * A kinds of the pin event is often selectable at CaptureModule#selectMode.
 * A base timer is also selectable at CaptureModule#selectBaseTimer.
 * The got timer count is obtained at CaptureModule#getCapturedCount.
 */
typedef struct {
	/**
	 * Enable capture module.
	 */
	void (*enable)(void);

	/**
	 * Disable capture module.
	 */
	void (*disable)(void);

	/**
	 * Select base timer for capture module.
	 *
	 * If no selectable timer exists, do nothing.
	 *
	 * @param identifier of base timer
	 */
	void (*selectBaseTimer)(char);

	/**
	 * Select operating mode of capture module.
	 *
	 * @param identifier of capture module operating mode
	 */
	void (*selectMode)(char);

	/**
	 * Get the captured timer count value/
	 *
	 * If capture event occured when reading captured count,
	 * the value may be uncorrect.
	 */
	uint16_t (*getCapturedCount)(void);
} CaptureModule;

/**
 * Compare presetting count value with base timer count value.
 *
 * On compare matched, a event occur.
 * The event may be user settable. (ex: software interrupt)
 */
typedef struct {
	/**
	 * Enable compare module
	 */
	void (*enable)(void);

	/**
	 * Disable compare module
	 */
	void (*disable)(void);

	/**
	 * Select base timer for capture module.
	 *
	 * If no selectable timer exists, do nothing.
	 *
	 * @param identifier of base timer
	 */
	void (*selectBaseTimer)(char);

	/**
	 * Select operating mode of compare module.
	 *
	 * @param identifier of compare module operating mode
	 */
	void (*selectMode)(char);

	/**
	 * Set count value compared with base timer count.
	 *
	 * The count value range depend on that of base timer.
	 */
	void (*setComparedCount)(uint16_t);
} CompareModule;

/**
 * Configurator of PWM output.
 */
typedef struct {
	/**
	 * Enable PWM module.
	 */
	void (*enable)(void);

	/**
	 * Disable PWM module.
	 */
	void (*disable)(void);

	/**
	 * Select base timer for PWM module.
	 *
	 * If no selectable timer exists, do nothing.
	 *
	 * @param identifier of base timer
	 */
	void (*selectBaseTimer)(char);

	/**
	 * Set duty cycle count.
	 *
	 * @param duty cycle count
	 */
	void (*setDutyCycle)(uint16_t);

	/**
	 * Select output configuration.
	 *
	 * @param identifier of output configuration
	 */
	void (*selectOutputConfig)(char);

	/**
	 * Select output polarity.
	 *
	 * @parama identifier of output polarity
	 */
	void (*selectOutputPolarity)(char);
} PWMModule;

#endif
