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
	/** enable PLL. */
	void (*enablePLL)(void);
	/** disable PLL. */
	void (*disablePLL)(void);
} PhaseLockedLoop;

typedef struct {
	/**
	 * Select a system clock mode.
	 * To find settable modes, see OscillatorModule.c.
	 * @param system clock mode
	 */
	void (*selectSystemClock)(int mode);
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
