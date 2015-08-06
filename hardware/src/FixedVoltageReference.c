#include "Hardware.h"
#include <xc.h>

// ----------------------------------------------------------------------------
// FixedVoltageReference_Constants
// ----------------------------------------------------------------------------
enum FixedVoltageReference_Buffer1Reference_Constants {
	B1_OFF       = 0b11110000,
	B1_OUTPUT_1x = 0b11110001,
	B1_OUTPUT_2x = 0b11110010,
	B1_OUTPUT_4x = 0b11110011,
};
const struct FixedVoltageReference_Buffer1Reference FixedVoltageReference_Buffer1Reference = {
	B1_OFF,
	B1_OUTPUT_1x,
	B1_OUTPUT_2x,
	B1_OUTPUT_4x,
};

enum FixedVoltageReference_Buffer2Reference_Constants {
	B2_OFF       = 0b00001111,
	B2_OUTPUT_1x = 0b00011111,
	B2_OUTPUT_2x = 0b00101111,
	B2_OUTPUT_4x = 0b00111111,
};
const struct FixedVoltageReference_Buffer2Reference FixedVoltageReference_Buffer2Reference = {
	B2_OFF,
	B2_OUTPUT_1x,
	B2_OUTPUT_2x,
	B2_OUTPUT_4x,
};

// ----------------------------------------------------------------------------
// FixedVoltageReference
// ----------------------------------------------------------------------------
#define FixedVoltageReference_(name) FixedVoltageReference_##name
static void FixedVoltageReference_(enable)() {
	FVRCONbits.FVREN = 1;
}

static void FixedVoltageReference_(disable)() {
	FVRCONbits.FVREN = 0;
}

static void FixedVoltageReference_(selectReference)(char ref) {
	if(ref & 0b1111 != 0b1111) {
		FVRCONbits.ADFVR = ref;
	}
	if(ref >> 4 != 0b1111) {
		FVRCONbits.CDAFVR = ref >> 4;
	}
}

static bool FixedVoltageReference_(isReady)() {
	return FVRCONbits.FVRRDY;
}

const FixedVoltageReference FixedVoltageReference_(instance) = {
	FixedVoltageReference_(enable),
	FixedVoltageReference_(disable),
	FixedVoltageReference_(selectReference),
	FixedVoltageReference_(isReady),
};
