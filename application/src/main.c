#include "Hardware.h"
#include <stdbool.h>

// function prototype
void setupOscillator(void);

static const IOPort* port;
static const ADConverterModule* adc;
static const TimerModule* timer;

int adcResult;

static void onConverted() {
	adcResult = adc->getResult();
}

InterruptListener adcListener = {
	onConverted,
};

void setup() {
	setupOscillator();
	port = Hardware.PortA;
	port->setPinModes(0b11111111, IOPort_PinMode.DIGITAL_OUTPUT);
	adc = Hardware.ADConverter;
	adc->enable();
	adc->selectInputChannel(ADConverterModule_InputChannel.AN0);
	const InterruptService* adcIntService = Hardware.ADConverterInterruptService;
	adcIntService->registerListener(&adcListener, InterruptService_Priority.DEFAULT);
	adcIntService->enableInterrupt();

	timer = Hardware.Timer0;
	timer->selectClockSource(Timer0Module_ClockSource.F_OSC_DIV_4);
	timer->selectPrescaler(Timer0Module_Prescaler.RATE_1_256);
	timer->setCount(0);
	timer->enable();
}

void loop() {
	port->write(0xFF);
	adc->startConversion();
}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}

void setupOscillator() {
	Hardware.Oscillator->selectSystemClockSource(
			OscillatorModule_ClockSource.INTERNAL);
	Hardware.InternalOscillator->selectFrequency(
			InternalOscillator_Frequency.HF_8MHz);
	Hardware.PhaseLockedLoop->enablePLL();
}

