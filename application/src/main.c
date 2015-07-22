#include "Hardware.h"
#include <stdbool.h>

static const IOPort* port;
static const ADConverterModule* adc;

int adcResult;

static void onConverted() {
	adcResult = adc->getResult();
}

InterruptListener adcListener = {
	onConverted,
};

void setup() {
	const OscillatorModule* osc = Hardware.OscillatorModule;
	osc->InternalOscillator->selectFrequency(
			InternalOscillator_Frequency.HF_8MHz);
	osc->PhaseLockedLoop->enablePLL();
	osc->selectSystemClockSource(
			OscillatorModule_ClockSource.INTERNAL);
	port = Hardware.PortA;
	port->setPinModes(0b11111111, IOPort_PinMode.DIGITAL_OUTPUT);
	adc = Hardware.ADConverterModule;
	adc->enable();
	adc->selectInputChannel(ADConverterModule_InputChannel.AN0);
	const InterruptService* adcIntService = Hardware.ADConverterModuleInterruptService;
	adcIntService->registerListener(&adcListener, InterruptService_Priority.DEFAULT);
	adcIntService->enableInterrupt();
}

void loop() {
	port->writeDigital(0xFF);
	adc->startConversion();
}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}

