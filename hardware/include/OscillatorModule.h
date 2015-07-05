#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

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
	 * returns InternalOscillator.
	 * @return interface of internal oscillator module
	 */
	InternalOscillator* (*InternalOscillator)(void);
	/**
	 * returns PhaseLockedLoop.
	 * @return interface of phase locked loop
	 */
	PhaseLockedLoop* (*PhaseLockedLoop)(void);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
