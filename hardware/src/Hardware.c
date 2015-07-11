#include "Hardware.h"

// declared at InterruptVector.c
extern InterruptVector* getInterruptVector(void);
// declared at OscillatorModule.c
extern OscillatorModule* getOscillatorModule(void);
// declared at IOPort.c
extern IOPort* PortA_getInstance(void);
extern IOPort* PortB_getInstance(void);
extern IOPort* PortC_getInstance(void);

const struct Hardware Hardware = {
	getInterruptVector,
	getOscillatorModule,
	PortA_getInstance,
	PortB_getInstance,
	PortC_getInstance,
};
	
