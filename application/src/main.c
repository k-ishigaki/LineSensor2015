#include "Hardware.h"
#include <stdbool.h>

IOPort* port;

void setup() {
	OscillatorModule* osc = hardware.OscillatorModule();
	osc->InternalOscillator()->setFrequency(8000000);
	osc->PhaseLockedLoop()->enablePLL();
	osc->selectSystemClockSource(
			osc->ClockSource()->INTERNAL_OSCILLATOR_BLOCK);
	port = hardware.PortA();
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

