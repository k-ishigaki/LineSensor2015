#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include <stdint.h>

/**
 * device's maximum timer counter size type.
 */
typedef uint16_t timer_module_counter_max_t;

/**
 * Timer gate control interface.
 */
typedef struct {

	/**
	 * Select gate count source.
	 *
	 * @param identifier of gate count source
	 */
	void (*selectSource)(char);

	/**
	 * Select gate control mode.
	 *
	 * @param identifier of gate control mode
	 */
	void (*selectMode)(char);

	/**
	 * Get current state of gate value.
	 *
	 * @return true if high-level, false if low-level
	 */
	bool (*getState)(void);

	/**
	 * Start single pulse aquisition.
	 *
	 * This method can be used when gate control mode is SINGLE_PULSE.
	 * If interrupt is enabled at
	 * TimerGateControlInterruptService#enableInterrupt, a interrupt
	 * occur at the end of aquisition.
	 * If you don't use interrupt, TimerGateControl#isWaitingSinglePulse
	 * is can be used for aquisition of a single pulse.
	 *
	 * example:
	 * {@code
	 * // timer module setup
	 * const TimerModule* tm = Hardware.Timer1Module;
	 * tm->enable();
	 * tm->selectClockSource(Timer1Module_ClockSource.XXX);
	 * tm->selectPrescaler(Timer1Module_Prescaler.XXX);
	 * tm->setMode(Timer1Module_Mode.COUNTER);
	 * tm->stop();
	 * tm->setCount(0);
	 * // timer gate control setup
	 * const TimerGateControl* tgc = tm->Timer1GateControl;
	 * tgc->selectSource(Timer1GateControl_Source.XXX);
	 * tgc->selectMode(Timer1GateControl_Mode.SINGLE_PULSE);
	 * // do single pulse aquisition and get result value
	 * tm->start();
	 * tgc->startSinglePulseAquisition();
	 * while(tgc->isWaitingSinglePulse());
	 * uint16_t result = tm->getCount();
	 * }
	 */
	void (*startSinglePulseAquisition)(void);

	/**
	 * Represent single pulse aquisition state.
	 *
	 * @return true if waiting single pulse edge<br>
	 * 	false if aquisition is completed or not conducted.
	 */
	bool (*isWaitingSinglePulse)(void);
} TimerGateControl;

/**
 * Timer module interface.
 * If you want to use timer overflow interrupt, use
 * TimerxModuleInterruptService (x is number or char identifier).
 */
typedef struct {

	/**
	 * Get counter value of timer module.
	 *
	 * @return counter value of timer module<br>
	 * 	(8bit timer) 0~255<br>
	 * 	(16bit timer) 0~65535
	 */
	timer_module_counter_max_t (*getCount)(void);

	/**
	 * Set counter value of timer module.
	 *
	 * @param counter value of timer module<br>
	 * 	(8bit timer) 0~255<br>
	 * 	(16bit timer) 0~65535
	 */
	void (*setCount)(timer_module_counter_max_t);

	/**
	 * Enable timer module and start Counting.
	 *
	 * If not enabled, countup is not occured.
	 */
	void (*enable)(void);

	/**
	 * Disable timer module and stop Counting.
	 */
	void (*disable)(void);

	/**
	 * Select clock source of timer count.
	 * 
	 * @param timer module clock source identifier
	 */
	void (*selectClockSource)(char);

	/**
	 * Select prescaler value of conting source.
	 *
	 * @param prescaler value identifier
	 */
	void (*selectPrescaler)(char);

	/**
	 * Select postscaler value of conting source.
	 *
	 * @param postscaler value identifier
	 */
	void (*selectPostscaler)(char);

	/**
	 * Select operating mode of timer module.
	 *
	 * @param operating mode identifier
	 */
	void (*selectMode)(char);

	/**
	 * Set timer period count.
	 *
	 * @param timer period count<br>
	 * 	do nothing if<br>
	 * 		count value is out of bounds<br>
	 * 		a timer module unsupport period count setting
	 */
	void (*setPeriodCount)(timer_module_counter_max_t);

	/**
	 * Timer module gate control interface.
	 *
	 * If a timer module has gate control, this interface can be used.
	 * You must switch to gate control mode with TimerModule#selectMode.
	 * The time module interfaces may be also tied to gate control.
	 * Please check data sheet for more details.
	 *
	 * @return interface of gate control<br>
	 * 	(if a timer module don't have it, return NULL)
	 */
	const TimerGateControl* TimerGateControl;
} TimerModule;

#endif /* TIMER_MODULE_H */
