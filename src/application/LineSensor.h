#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include "PhotoReflector.h"

struct LineSensor {
	const struct PhotoReflector* (*PhotoReflector0)(void);
	const struct PhotoReflector* (*PhotoReflector1)(void);
	const struct PhotoReflector* (*PhotoReflector2)(void);
	const struct PhotoReflector* (*PhotoReflector3)(void);
	const struct PhotoReflector* (*PhotoReflector4)(void);
	const struct PhotoReflector* (*PhotoReflector5)(void);
	const struct PhotoReflector* (*PhotoReflector6)(void);
	const struct PhotoReflector* (*PhotoReflector7)(void);
};

#endif /* LINE_SENSOR_H */
