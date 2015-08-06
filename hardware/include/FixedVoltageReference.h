#ifndef FIXED_VOLTAGE_REFERENCE_H
#define FIXED_VOLTAGE_REFERENCE_H

#include <stdbool.h>

typedef struct {
	/**
	 * Enable fixed voltage reference.
	 */
	void (*enable)(void);

	/**
	 * Disable fixed voltage reference.
	 */
	void (*disable)(void);

	/**
	 * Select voltage reference for output buffers.
	 *
	 * If multiple output buffers exist, please call this method in
	 * different way. for example:
	 * {@code
	 * const FixedVoltageReference* fvr = Hardware.FixedVoltageReference;
	 * fvr->enable();
	 * fvr->selectReference(
	 * 	FixedVoltageReference_Buffer1Reference.OUTPUT_2x
	 * 	& FixedVoltageReference_Buffer2Reference.OUTPUT_4x);
	 * }
	 *
	 * @param identifier of voltage reference for buffer output
	 */
	void (*selectReference)(char);

	/**
	 * Represent that fvr is ready for using.
	 *
	 * @return true if fvr output is ready for using<br>
	 * 	false if not
	 */
	bool (*isReady)(void);
} FixedVoltageReference;

#endif /* FIXED_VOLTAGE_REFERENCE_H */
