#include "Hardware.h"

// declared at InterruptVector.c
extern InterruptVector* getInterruptVector(void);
// declared at OscillatorModule.c
extern OscillatorModule* getOscillatorModule(void);

Hardware hardware = {
	getInterruptVector,
	getOscillatorModule,
};
	
