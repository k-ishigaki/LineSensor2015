#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

typedef struct {
	/**
	 * Set frequency of internal oscillator.
	 * If you select a invalid value, doing nothing.
	 * To find settable frequencies, see OscillatorModule.c.
	 * @param frequency(Hz)
	 */
	void (const *setFrequency)(unsigned long frequency);
} InternalOscillator;

typedef struct {
	/**
	 * Enable PLL.
	 */
	void (const *enablePLL)(void);
	/**
	 * disable PLL.
	 * Ensure the configuration word PLLEN = 0.
	 * If SPLLEN = 1, PLL is always enabled.
	 */
	void (const *disablePLL)(void);
} PhaseLockedLoop;

typedef struct {
	/**
	 * Select a system clock Source.
	 * To find settable clock sources, see OscillatorModule.c.
	 * @param system clock source
	 */
	void (const *selectSystemClockSource)(int clockSource);
	/**
	 * Returns InternalOscillator.
	 * @return interface of internal oscillator module
	 */
	const InternalOscillator* (*InternalOscillator)(void);
	/**
	 * Returns PhaseLockedLoop.
	 * @return interface of phase locked loop
	 */
	const PhaseLockedLoop* (*PhaseLockedLoop)(void);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
