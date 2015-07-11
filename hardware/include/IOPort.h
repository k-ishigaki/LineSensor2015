#ifndef IO_PORT_H
#define IO_PORT_H

#include <stdint.h>

/**
 * Defines IO port characteristics includes port configs.
 *
 * A function of ADC is not included because ADC module is not part of
 * IO port module.
 *
 * usage: write to output latch
 * {@code
 * IOPort port = Hardware.PortA; // get instance of Port A
 * port->setDigitalOutput(0xFF); // set all pins to digital output
 * port->writeDigital(0x55);     // pin 0, 2, 4, 6: output high
 *                               // pin 1, 3, 5, 7: output low
 * }
 *
 * usage: read port status
 * {@code
 * IOPort port = Hardware.PortA;
 * port->setDigitalInput(0xFF);          // set all pins to digital input
 * uint8_t result = port->readDigital(); // read port and store
 * }
 */
typedef struct {
	/**
	 * Set pins to analog input.
	 *
	 * The analog input pins are often used by ADC.
	 * Please check data sheet not to select unsupported pins.
	 * example:
	 * {@code setAnalogInput(0b00010001); // pin 0 and pin 4 selected}
	 *
	 * @param selected pin positions
	 */
	void (*setAnalogInput)(uint8_t);
	/**
	 * Set pins to analog output.
	 *
	 * The analog output pins are often used by DAC.
	 * Please check data sheet not to select unsupported pins.
	 * example:
	 * {@code setAnalogOutput(0b00010001); // pin 0 and pin 4 selected}
	 *
	 * @param selected pin positions
	 */
	void (*setAnalogOutput)(uint8_t);
	/**
	 * Set pins to digital input.
	 *
	 * Please check data sheet not to select unsupported pins.
	 * {@code setDigitalInput(0b00010001); // pin 0 and pin 4 selected}
	 *
	 * @param selected pin positions
	 */
	void (*setDigitalInput)(uint8_t);
	/**
	 * Set pins to digital input.
	 *
	 * Please check data sheet not to select unsupported pins.
	 * {@code setDigitalOutput(0b00010001); // pin 0 and pin 4 selected}
	 *
	 * @param selected pin positions
	 */
	void (*setDigitalOutput)(uint8_t);
	/**
	 * Read levels on the digital input pins.
	 *
	 * If a pin is not digital input, the return value is not specified.
	 *
	 * @return 1 if high level , else 0 for respective pins
	 */
	uint8_t (*readDigital)(void);
	/**
	 * Write outputs to digital output pins.
	 *
	 * If a pin is not digital output, its state is unchanged.
	 *
	 * @param a output levels for respective pins<br>
	 * 	1 = output high<br>
	 * 	0 = output low
	 */
	void (*writeDigital)(uint8_t);
} IOPort;

#endif /* IO_PORT_H */
