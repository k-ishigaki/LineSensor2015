#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

typedef struct {
	/**
	 * Select frequency of internal oscillator.
	 * To find selectable frequencies, see Hardware.h.
	 * @param frequency identifier
	 */
	void (*selectFrequency)(char);
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
	 * @param system clock source identifier
	 */
	void (*selectSystemClockSource)(char);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
