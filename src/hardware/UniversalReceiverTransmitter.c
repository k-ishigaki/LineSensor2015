#include <xc.h>
#include "Hardware.h"

// ----------------------------------------------------------------------------
// EUSART constants
// ----------------------------------------------------------------------------
enum UniversalReceiverTransmitter_Mode_Constant {
	ASYNCHRONOUS,
	SYNCHRONOUS_MASTER,
	SYNCHRONOUS_SLAVE,
};
const struct UniversalReceiverTransmitter_Mode UniversalReceiverTransmitter_Mode = {
	ASYNCHRONOUS,
	SYNCHRONOUS_MASTER,
	SYNCHRONOUS_SLAVE,
};

enum UniversalReceiverTransmitter_ReceiveMode_Constant {
	R_EIGHT_BIT                  = 0b00,
	R_NINE_BIT                   = 0b01,
	R_NINE_BIT_ADDRESS_DETECTION = 0b11,
};
const struct UniversalReceiverTransmitter_ReceiveMode UniversalReceiverTransmitter_ReceiveMode = {
	R_EIGHT_BIT,
	R_NINE_BIT,
	R_NINE_BIT_ADDRESS_DETECTION,
};

enum UniversalReceiverTransmitter_TransmitMode_Constant {
	T_EIGHT_BIT = 0,
	T_NINE_BIT  = 1,
};
const struct UniversalReceiverTransmitter_TransmitMode UniversalReceiverTransmitter_TransmitMode = {
	T_EIGHT_BIT,
	T_NINE_BIT,
};

enum UniversalReceiverTransmitter_Polarity_Constant {
	NON_INVERTED_OR_FALLING_EDGE = 0,
	INVERTED_OR_RISING_EDGE      = 1,
};
const struct UniversalReceiverTransmitter_Polarity UniversalReceiverTransmitter_Polarity = {
	NON_INVERTED_OR_FALLING_EDGE,
	INVERTED_OR_RISING_EDGE,
};

enum UniversalReceiverTransmitter_Error_Constant {
	FRAMING = 0b10,
	OVERRUN = 0b01,
};
const struct UniversalReceiverTransmitter_Error UniversalReceiverTransmitter_Error = {
	FRAMING,
	OVERRUN,
};

// ----------------------------------------------------------------------------
// EUSART interface
// ----------------------------------------------------------------------------
#define UniversalReceiverTransmitter_(name) UniversalReceiverTransmitter_##name

static uint16_t UniversalReceiverTransmitter_(read)() {
	// RCSTA<0> = RX9D
	return RCREG + ((uint16_t)(RCSTA & 0b00000001) << 8);
}

static bool UniversalReceiverTransmitter_(hasReceived)() {
	return PIR1bits.RCIF;
}

static void UniversalReceiverTransmitter_(write)(uint16_t data) {
	while(!TXSTAbits.TRMT);
	TXSTAbits.TX9D = data >> 8;
	TXREG = data;
}

static bool UniversalReceiverTransmitter_(isTransmitting)() {
	return !TXSTAbits.TRMT;
}

static void UniversalReceiverTransmitter_(resetReceiver)() {
	RCSTAbits.SPEN = 0;
	RCSTAbits.SPEN = 1;
}

static uint8_t UniversalReceiverTransmitter_(getErrors)() {
	// get FERR bit and OERR bit
	// RCSTA<2> = FERR
	// RCSTA<1> = OERR
	return (RCSTA & 0b00000110) >> 1;
}

static const UniversalReceiverTransmitter UniversalReceiverTransmitter_(instance) = {
	UniversalReceiverTransmitter_(read),
	UniversalReceiverTransmitter_(hasReceived),
	UniversalReceiverTransmitter_(write),
	UniversalReceiverTransmitter_(isTransmitting),
	UniversalReceiverTransmitter_(resetReceiver),
	UniversalReceiverTransmitter_(getErrors),
};

// ----------------------------------------------------------------------------
// EUSART constructor
// ----------------------------------------------------------------------------
const UniversalReceiverTransmitter* UniversalReceiverTransmitter_(constructor)(
		char mode,
		char receiveMode,
		char transmitMode,
		char polarity,
		unsigned long baudrate){
	// only asynchronous mode can be used
	// decide receive mode and transmit mode
	RCSTAbits.RX9 = receiveMode;
	RCSTAbits.ADDEN = receiveMode >> 1;
	TXSTAbits.TX9 = transmitMode;
	// decide polarity
	BAUDCONbits.SCKP = polarity;
	// decide baudrate
	uint16_t spbrg = OPERATING_FREQUENCY / (4 * baudrate) - 1;
	SPBRGH = spbrg >> 8;
	SPBRGL = spbrg;
	BAUDCONbits.BRG16 = 1;
	TXSTAbits.BRGH = 1;
	// enable serial port
	TXSTAbits.TXEN = 1;
	RCSTAbits.CREN = 1;
	RCSTAbits.SPEN = 1;
	// return instance
	return &UniversalReceiverTransmitter_(instance);
}

