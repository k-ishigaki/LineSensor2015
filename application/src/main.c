#include "Hardware.h"
#include <stdbool.h>

void setup() {
	OscillatorModule* osc = hardware.getOscillatorModule();
	osc->getInternalOscillator()->setFrequency(8000000);
	osc->getPhaseLockedLoop()->enablePLL();
	osc->selectSystemClockSource(INTERNAL_OSCILLATOR_BLOCK);
}

void loop() {

}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}

