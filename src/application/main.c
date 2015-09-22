#include "Hardware.h"
#include <stdbool.h>
#include <stdio.h>
#include <xc.h>

#define _XTAL_FREQ OPERATING_FREQUENCY

// RA0 and RA1 are used for debug serial port
// (RA0 : TX, RA1 : RX)
#define RA0_A0_PIN  0b00000001
#define RA1_A1_PIN  0b00000010
#define RA2_A2_PIN  0b00000100
#define RA4_A3_PIN  0b00010000
#define RA5_nSW_PIN 0b00100000
#define RC0_SCL_PIN 0b00000001
#define RC1_SDA_PIN 0b00000010
#define RC2_D0_PIN  0b00000100
#define RC3_D1_PIN  0b00001000
#define RC4_D2_PIN  0b00010000
#define RC5_D3_PIN  0b00100000

static const struct IOPort* portA;
static const struct IOPort* portC;
static const struct ADConverter* adc;
static const TimerModule* timer;
static const struct USART* serial;

void onADCInterrupt() {
	// do something
}

InterruptListener ADIntListener = {
	onADCInterrupt,
};

void putch(char data) {
	serial->write(data);
}

void setup() {
	Hardware.configureAlternatePinFunction(
			AlternatePinFunction_RXAndDT.RA1,
			AlternatePinFunction_SDO.RA4,
			AlternatePinFunction_SS.RA3,
			AlternatePinFunction_T1G.RA3,
			AlternatePinFunction_TXAndCK.RA0,
			AlternatePinFunction_P1D.RC0,
			AlternatePinFunction_P1C.RC1,
			AlternatePinFunction_P2B.RA4,
			AlternatePinFunction_CCP2.RA5);
	Hardware.configureOscillator(
			OscillatorModule_InternalClockFrequency.HF_8MHz,
			OscillatorModule_PhaseLockedLoop.ENABLE,
			OscillatorModule_SystemClockSource.DETERMINED_BY_CONFIG);
	portA = Hardware.PortA();
	portC = Hardware.PortC();

	// photo transister input pins
	portA->setPinModes(
			RA0_A0_PIN | RA1_A1_PIN | RA2_A2_PIN | RA4_A3_PIN,
			IOPort_PinMode.ANALOG_INPUT);
	// switch input pin
	portA->setPinModes(
			RA5_nSW_PIN,
			IOPort_PinMode.DIGITAL_INPUT_WITH_INTERNAL_PULLUP);

	// debug serial TX pin
	portA->setPinModes(RA0_A0_PIN, IOPort_PinMode.DIGITAL_OUTPUT);
	// debug serial RX pin
	portA->setPinModes(RA1_A1_PIN, IOPort_PinMode.DIGITAL_INPUT);
	// i2c pins
	portC->setPinModes(
			RC0_SCL_PIN | RC1_SDA_PIN,
			IOPort_PinMode.ANALOG_INPUT);
	// led nch fet gate pins
	portC->setPinModes(
			RC2_D0_PIN | RC3_D1_PIN | RC4_D2_PIN | RC5_D3_PIN,
			IOPort_PinMode.DIGITAL_OUTPUT);

	// all leds off
	portC->write(RC2_D0_PIN | RC3_D1_PIN | RC4_D2_PIN | RC5_D3_PIN, 0x00);

	adc = Hardware.ADConverterModule(
			ADConverterModule_PositiveReference.VDD,
			ADConverterModule_NegativeReference.VSS,
			ADConverterModule_ConversionClock.F_OSC_DIV_32);

	const InterruptService* adcIntSer = Hardware.ADConverterInterruptService();
	adcIntSer->registerListener(&ADIntListener);
	adcIntSer->enableInterrupt();

	timer = Hardware.Timer0(
			Timer0Module_ClockSource.F_OSC_DIV_4,
			Timer0Module_Prescaler.RATE_1_1);
	timer->setCount(0);
	timer->start();

	serial = Hardware.EUSART(
			EUSART_Mode.ASYNCHRONOUS,
			EUSART_ReceiveMode.EIGHT_BIT,
			EUSART_TransmitMode.EIGHT_BIT,
			EUSART_Polarity.NON_INVERTED_OR_FALLING_EDGE,
			115200L);
}

void loop() {
	for (int i = 0; i < 100; i++) {
		__delay_ms(10);
	}
	portC->toggle(RC4_D2_PIN);
	adc->selectInputChannel(ADConverterModule_InputChannel.AN1);
	__delay_us(100);
	adc->startConversion();
	while(adc->isConverting());
	unsigned int res = adc->getResult();
	portC->toggle(RC4_D2_PIN);
	printf("res = %d\n",res);

	if(!(portA->read() & RA5_nSW_PIN)) {
		printf("pushed\n");
	}

	serial->write('A');
	serial->write('B');
	serial->write('C');
	serial->write('D');
	serial->write('\n');
}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}
