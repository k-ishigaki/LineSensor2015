#include "Hardware.h"
#include <stdbool.h>

static const IOPort* port;

void setup() {
	const OscillatorModule* osc = Hardware.OscillatorModule;
	osc->InternalOscillator->setFrequency(8000000);
	osc->PhaseLockedLoop->enablePLL();
	osc->selectSystemClockSource(
			OscillatorModule_ClockSource.INTERNAL);
	port = Hardware.PortA;
	port->setDigitalOutput(0b11111111);
}

void loop() {
	port->writeDigital(0xFF);
}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}

