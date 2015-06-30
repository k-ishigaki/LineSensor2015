#include "Hardware.h"
#include "OscillatorModule.h"

extern OscillatorModule* getOscillatorModule(void); // defined at OscillatorModule.c

Hardware hardware = {
	getOscillatorModule,
};
	
