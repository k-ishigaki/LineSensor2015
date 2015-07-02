#include "Hardware.h"

extern OscillatorModule* getOscillatorModule(void); // defined at OscillatorModule.c

Hardware hardware = {
	getOscillatorModule,
};
	
