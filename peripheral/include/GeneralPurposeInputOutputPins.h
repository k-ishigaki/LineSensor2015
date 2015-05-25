#ifndef GENERAL_PURPOSE_INPUT_OUTPUT_PINS
#define GENERAL_PURPOSE_INPUT_OUTPUT_PINS

#include <stdbool.h>

/** GPIO Interface */
typedef struct {
	void (*setAnalogInput)(void);
} AnalogInputPin;

typedef struct {
	void (*setDigitalInput)(void);
	bool (*getPinState)(void);
} DigitalInputPin;

typedef struct {
	void (*setDigitalOutput)(void);
	void (*setPinState)(void);
} DigitalOutputPin;

typedef struct {
	void (*setDirection)(bool);
	void (*setPinState)(bool);
	bool (*getPinState)(void);
} GeneralPurposeInputOutputPin;

/** analog inputable pin */
typedef struct {
	AnalogInputPin* (*getAnalogInputPin)(void);
	DigitalInputPin* (*getDigitalInputPin)(void);
	DigitalOutputPin* (*getDigitalOutputPin)(void);
	GeneralPurposeInputOutputPin* (*getGeneralPurposeInputOutputPin)(void);
} AnalogInputablePin;

/** digital pin */
typedef struct {
	DigitalInputPin* (*getDigitalInputPin)(void);
	DigitalOutputPin* (*getDigitalOutputPin)(void);
	GeneralPurposeInputOutputPin* (*getGeneralPurposeInputOutputPin)(void);
} DigitalPin;

/** digital input only pin */
typedef struct {
	DigitalInputPin* (*getDigitalInputPin)(void);
} DigitalInputOnlyPin;

#endif /* GENERAL_PURPOSE_INPUT_OUTPUT_PINS */
