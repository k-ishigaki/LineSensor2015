#include <xc.h>
#include "peripheral_GeneralPurposeInputOutputPin.h"
#define GPIO(name) peripheral_GeneralPurposeInputOutputPin_##name 

GPIO(DigitalOutputPin)* output;

int main(void) {
	// do nothing
}
