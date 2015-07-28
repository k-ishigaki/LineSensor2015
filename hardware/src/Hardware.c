#include "Hardware.h"

// declared at InterruptVector.c
extern const InterruptService ADConverterModuleInterruptService_instance;
extern const InterruptService Timer0ModuleInterruptService_instance;
extern const InterruptService Timer1ModuleInterruptService_instance;
extern const InterruptService Timer2ModuleInterruptService_instance;
extern const InterruptService Timer4ModuleInterruptService_instance;
extern const InterruptService Timer6ModuleInterruptService_instance;
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
extern const TimerGateControl Timer1GateControl_instance;
extern const TimerModule Timer2Module_instance;
extern const TimerModule Timer4Module_instance;
extern const TimerModule Timer6Module_instance;

const struct Hardware Hardware = {
	&ADConverterModuleInterruptService_instance,
	&Timer0ModuleInterruptService_instance,
	&Timer1ModuleInterruptService_instance,
	&Timer2ModuleInterruptService_instance,
	&Timer4ModuleInterruptService_instance,
	&Timer6ModuleInterruptService_instance,
	&OscillatorModule_instance,
	&InternalOscillator_instance,
	&PhaseLockedLoop_instance,
	&PortA_instance,
	&PortB_instance,
	&PortC_instance,
	&ADConverterModule_instance,
	&Timer0Module_instance,
	&Timer1Module_instance,
	&Timer1GateControl_instance,
	&Timer2Module_instance,
	&Timer4Module_instance,
	&Timer6Module_instance,
};
