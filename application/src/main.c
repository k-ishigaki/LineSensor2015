#include "Hardware.h"
#include <stdbool.h>

void setup() {
	OscillatorModule* osc = hardware.OscillatorModule();
	osc->InternalOscillator()->setFrequency(8000000);
	osc->PhaseLockedLoop()->enablePLL();
	osc->selectSystemClockSource(OSC_INTERNAL_OSCILLATOR_BLOCK);
}

void loop() {

}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}

