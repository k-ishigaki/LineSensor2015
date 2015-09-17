#ifndef UNIVERSAL_RECEIVER_TRANSMITTER_H
#define UNIVERSAL_RECEIVER_TRANSMITTER_H

#include <stdint.h>

typedef struct {
	/**
	 * Read from receive buffer.
	 *
	 * Before reading from the buffer, you must confirm that data exists
	 * in it.
	 *
	 * @return received data in receive buffer
	 */
	uint16_t (*read)(void);

	/**
	 * Represent receive buffer status.
	 *
	 * If UniversalReceiverTransmitter#read method can be used, this
	 * method returns true.
	 * To read from received buffer, see UniversalReceiverTransmitter#read.
	 *
	 * @return true if received data exits<br>
	 * 	false if no data exits.
	 */
	bool (*hasReceived)(void);

	/**
	 * Write to transmit buffer of the module.
	 *
	 * Before writing to the buffer, you must confirm that it is empty.
	 * {@code
	 * const UniversalReceiverTransmitter* serial = Hardware.EUSART;
	 * ... (setup serial module)
	 * while(serial->isTransmitting);
	 * serial->write(data);
	 * }
	 *
	 * @param transmitting data to transmit buffer
	 */
	void (*write)(uint16_t);

	/**
	 * Represent transmit buffer status.
	 *
	 * If UniversalReceiverTransmitter#write method can be used, this
	 * method returns true.
	 * To write to transmit buffer, see UniversalReceiverTransmitter#write.
	 * 
	 * @return true if transmit buffer is full<br>
	 * 	false if it is empty
	 */
	bool (*isTransmitting)(void);

	/**
	 * Reset reciver and re-enable it.
	 *
	 * When UniversalReceiverTransmitter#getErrors != 0, clearing flag
	 * may be needed.
	 * Using this method, the errors can be cleared.
	 */
	void (*resetReceiver)(void);

	/**
	 * Get errors in receiver.
	 *
	 * If you want to detect which errors occured, use
	 * UniversalReceiverTransmitter_Error constants defined at Hardware.h.
	 * {@code
	 * const UniversalReceiverTransmitter uasrt = Hardware.
	 * 	UniversalReceiverTransmitter(...);
	 * uint8_t error = usart->getErrors();
	 * if(error & UniversalReceiverTransmitter_Error.OVERRUN) {
	 * 	// overrun error occured
	 * } else if (error & UniversalReceiverTransmitter_Error.FRAMING) {
	 * 	// framing error occured
	 * }
	 * }
	 *
	 * @return 0 if no error occurs<br>
	 * 	the kinds of error can be detect by<br>
	 * 	UniversalReceiverTransmitter_Error
	 */
	uint8_t (*getErrors)(void);
} UniversalReceiverTransmitter;

#endif /* UNIVERSAL_RECEIVER_TRANSMITTER_H */
