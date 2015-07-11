#include "Hardware.h"

// declared at InterruptVector.c
extern const InterruptVector InterruptVector_instance;
// declared at OscillatorModule.c
extern const OscillatorModule OscillatorModule_instance;
// declared at IOPort.c
extern const IOPort PortA_instance;
extern const IOPort PortB_instance;
extern const IOPort PortC_instance;

const struct Hardware Hardware = {
	&InterruptVector_instance,
	&OscillatorModule_instance,
	&PortA_instance,
	&PortB_instance,
	&PortC_instance,
};
