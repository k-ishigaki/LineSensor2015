#ifndef GENERAL_PURPOSE_INPUT_OUTPUT_PINS
#define GENERAL_PURPOSE_INPUT_OUTPUT_PINS

#include <stdbool.h>

/** GPIO Interface */
typedef struct {
	void (*setDigitalInput)(void);
	void (*setDigitalOutput)(void);
	void (*setPinState)(bool);
	bool (*getPinState)(void);
} GPIOPin;

/** PORT A IO definition */
typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA0;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA1;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA2;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA3;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA4;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA5;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA6;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RA7;

/** PORT B IO definition */
typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB0;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB1;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB2;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB3;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB4;

typedef struct {
	void (*setAnalogInput)(void);
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB5;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB6;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RB7;

/** PORT C IO definition */
typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC0;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC1;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC2;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC3;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC4;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC5;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC6;

typedef struct {
	GPIOPin* (*getGPIOPin)(void);
} GPIOPin_RC7;

/** PORT E IO definition */
typedef struct {
	void (*setDigitalInput)(void);
	bool (*getPinState)(void);
} GPIOPin_RE3;

#endif /* GENERAL_PURPOSE_INPUT_OUTPUT_PINS */
