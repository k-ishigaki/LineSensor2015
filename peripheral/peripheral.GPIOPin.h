#ifndef PERIPHERAL_GENERAL_PURPOSE_INPUT_OUTPUT_PIN
#define PERIPHERAL_GENERAL_PURPOSE_INPUT_OUTPUT_PIN
#define namespace(name) peripheral_GeneralPurposeInputOutputPin_##name

#include <stdbool.h>

/** GPIO Interface */
typedef struct {
	bool (*getPinState)(void);
} namespace(DigitalInputPin);

typedef struct {
	void (*setPinState)(void);
} namespace(DigitalOutputPin);

typedef struct {
	void (*setDirection)(bool);
	void (*setPinState)(bool);
	bool (*getPinState)(void);
} namespace(GeneralPurposeInputOutputPin);

/** analog inputable pin */
typedef struct {
	void (*setAnalogInput)(void);
	namespace(DigitalInputPin)* (*getDigitalInputPin)(void);
	namespace(DigitalOutputPin)* (*getDigitalOutputPin)(void);
	namespace(GeneralPurposeInputOutputPin)* (*getGeneralPurposeInputOutputPin)(void);
} namespace(AnalogInputablePin);

/** digital pin */
typedef struct {
	namespace(DigitalInputPin)* (*getDigitalInputPin)(void);
	namespace(DigitalOutputPin)* (*getDigitalOutputPin)(void);
	namespace(GeneralPurposeInputOutputPin)* (*getGeneralPurposeInputOutputPin)(void);
} namespace(DigitalPin);

/** digital input only pin */
typedef struct {
	namespace(DigitalInputPin)* (*getDigitalInputPin)(void);
} namespace(DigitalInputOnlyPin);

namespace(AnalogInputablePin)* getRA0(void);
namespace(AnalogInputablePin)* getRA1(void);
namespace(AnalogInputablePin)* getRA2(void);
namespace(AnalogInputablePin)* getRA3(void);
namespace(AnalogInputablePin)* getRA4(void);
namespace(AnalogInputablePin)* getRA5(void);
namespace(AnalogInputablePin)* getRA6(void);
namespace(AnalogInputablePin)* getRA7(void);

#undef namespace
#endif /* PERIPHERAL_GENERAL_PURPOSE_INPUT_OUTPUT_PIN */
