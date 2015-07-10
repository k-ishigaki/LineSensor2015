#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

/** defined at Hardware.h */
struct OscillatorModule_ClockSource;

typedef struct {
	/**
	 * Set frequency of internal oscillator.
	 * If you select a invalid value, doing nothing.
	 * To find settable frequencies, see OscillatorModule.c.
	 * @param frequency(Hz)
	 */
	void (*setFrequency)(unsigned long frequency);
} InternalOscillator;

typedef struct {
	/**
	 * Enable PLL.
	 */
	void (*enablePLL)(void);
	/**
	 * disable PLL.
	 * Ensure the configuration word PLLEN = 0.
	 * If SPLLEN = 1, PLL is always enabled.
	 */
	void (*disablePLL)(void);
} PhaseLockedLoop;

typedef struct {
	/**
	 * Select a system clock Source.
	 * To find settable clock sources, see OscillatorModule.c.
	 * @param system clock source
	 */
	void (*selectSystemClockSource)(int clockSource);
	/**
	 * Returns InternalOscillator.
	 * @return interface of internal oscillator module
	 */
	InternalOscillator* (*InternalOscillator)(void);
	/**
	 * Returns PhaseLockedLoop.
	 * @return interface of phase locked loop
	 */
	PhaseLockedLoop* (*PhaseLockedLoop)(void);
	/**
	 * Returns ClockSource enumuration constants.
	 * @return clock source enumuration constants
	 */
	const struct OscillatorModule_ClockSource* (*ClockSource)(void);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
