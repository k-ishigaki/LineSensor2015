#ifndef LED_H
#define LED_H

#include "DigitalPin.h"

struct LED {
	void (*turnOn)(void);
	void (*turnOff)(void);
};

const struct LED* createLED(
		const struct DigitalPin* pin);

#endif /* LED_H */
