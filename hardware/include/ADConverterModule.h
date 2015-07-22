#ifndef AD_CONVERTER_MODULE_H
#define AD_CONVERTER_MODULE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Represents analog to digital converter module.
 * 
 */
typedef struct {

	/**
	 * Get digital resolution of the AD converter.
	 * 
	 * The return value unit is bit.
	 * {@code
	 * const ADConverterModule* adc = Hardware.ADConverterModule;
	 * char a = adc->getResolution(); // returns 10 (PIC16F1938)
	 * }
	 *
	 * @return digital resolution of the ADC (bit)
	 */
	char (*getResolution)(void);

	/**
	 * Select positive reference voltage source of the AD converter.
	 *
	 * Default value depends on the device, please check at data sheet.
	 * The selectable constants are defined at Hardware.h.
	 *
	 * @param positive reference voltage source constant
	 */
	void (*selectPositiveReference)(char);

	/**
	 * Select negative reference voltage source of the AD converter.
	 *
	 * Default value depends on the device, please check at data sheet.
	 * The selectable constants are defined at Hardware.h.
	 *
	 * @param negative reference voltage source constant
	 */
	void (*selectNegativeReference)(char);

	/**
	 * Select conversion clock of the AD converter.
	 *
	 * If conversion clock is too fast, the results may be incorrect.
	 * So, please refer to the data sheet of the device.
	 * The selectable constants are defined at Hardware.h.
	 *
	 * @param conversion clock speed identifier
	 */
	void (*selectConversionClock)(char);

	/**
	 * Select input channel of the AD conveter.
	 *
	 * Please ensure the pin is analog inputable before connect
	 * ad conveter input channel to it.
	 * AD conveter often needs acquisition time, so you should make time
	 * before call {@code ADConverterModule#startConversion} when input
	 * channel is changed.
	 * The channel identifier is defined at Hardware.h
	 * 
	 * @param input channel identifier
	 */
	void (*selectInputChannel)(char);

	/**
	 * Power on the AD converer module.
	 *
	 * Before call {@code ADConverterModule#startConversion}, you should
	 * make sure the module is enabled.
	 */
	void (*enable)(void);

	/**
	 * Power off the AD converter module.
	 *
	 * If you don't use the module and want to save the electric power,
	 * it is recommended to use this method.
	 */
	void (*disable)(void);

	/**
	 * Initiate AD conversion cycle.
	 *
	 * The AD conversion is started if previous conversion is ended.
	 * If previous one continues, wait for it is finished. So, please
	 * note that this method may take time.
	 *
	 * Before start conversion, {@code ADConverterModule#eneble} and
	 * (if needed) {@code ADConverterModule#selectInputChannel} should
	 * be called.
	 *
	 * If interrupt is enabled by ADConverterModuleInterruptService,
	 * the registered listener is called at finish of the convertion.
	 */
	void (*startConversion)(void);

	/**
	 * Return whether AD conversion continues or not.
	 *
	 * If you don't use interrupt of AD converter module, it is recommended
	 * using this method after ADConverterModule#startConversion.
	 *
	 * example:
	 * {@code
	 * adc->startConversion();
	 * while(adc->isConverting()); // wait for finishing conversion
	 * int result = adc->getResult();
	 * }
	 *
	 * @return true if AD conversion continues, false if not
	 */
	bool (*isConverting)(void);

	/**
	 * Get result value of previous AD conversion.
	 *
	 * The resolution of AD conversion can be obtained from
	 * ADConverterModule#getResolution.
	 *
	 * @return result value of previous AD conversion
	 */
	unsigned long (*getResult)(void);
} ADConverterModule;

#endif /* AD_CONVERTER_MODULE_H */
