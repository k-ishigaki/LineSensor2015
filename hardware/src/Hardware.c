#include "Hardware.h"

// declared at InterruptVector.c
extern const InterruptService ADConverterModuleInterruptService_instance;
// declared at OscillatorModule.c
extern const OscillatorModule OscillatorModule_instance;
extern const InternalOscillator InternalOscillator_instance;
extern const PhaseLockedLoop PhaseLockedLoop_instance;
// declared at IOPort.c
extern const IOPort PortA_instance;
extern const IOPort PortB_instance;
extern const IOPort PortC_instance;
// declared at ADConverterModule.c
extern const ADConverterModule ADConverterModule_instance;
// declared at TimerModule.c
extern const TimerModule Timer0Module_instance;
extern const TimerModule Timer1Module_instance;

const struct Hardware Hardware = {
	&ADConverterModuleInterruptService_instance,
	&OscillatorModule_instance,
	&InternalOscillator_instance,
	&PhaseLockedLoop_instance,
	&PortA_instance,
	&PortB_instance,
	&PortC_instance,
	&ADConverterModule_instance,
	&Timer0Module_instance,
	&Timer1Module_instance,
};
