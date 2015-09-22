#include "PhotoReflector.h"

#include "LED.h"
#include "PhotoTransistor.h"

#ifndef COMMON_DECLARATION
#define COMMON_DECLARATION

static void turnOn_dummy() {
}
static void turnOff_dummy() {
}
static const struct LED LED_dummy = {
	turnOn_dummy,
	turnOff_dummy,
};

static int read_dummy() {
	return 0;
}
static const struct PhotoTransistor PhotoTransistor_dummy = {
	read_dummy,
};

static const struct PhotoReflector* PhotoReflector0_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector1_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector2_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector3_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector4_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector5_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector6_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector7_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector8_constructor(const struct LED*, const struct PhotoTransistor*);
static const struct PhotoReflector* PhotoReflector9_constructor(const struct LED*, const struct PhotoTransistor*);

static const struct PhotoReflector* (*PhotoReflector_constructor[10])(const struct LED*, const struct PhotoTransistor*) = {
	PhotoReflector0_constructor,
	PhotoReflector1_constructor,
	PhotoReflector2_constructor,
	PhotoReflector3_constructor,
	PhotoReflector4_constructor,
	PhotoReflector5_constructor,
	PhotoReflector6_constructor,
	PhotoReflector7_constructor,
	PhotoReflector8_constructor,
	PhotoReflector9_constructor,
};

const struct PhotoReflector* createPhotoReflector(
		const struct LED* led,
		const struct PhotoTransistor* photoTransistor) {
	static char index = 0;
	return PhotoReflector_constructor[index++](
			led,
			photoTransistor);
}
#endif /* COMMON_DECLARATION */

#if !defined(PHOTO_REFLECTOR0_DECLARED)
#define PHOTO_REFLECTOR0_DECLARED
#define this_(name) PhotoReflector0_##name

#elif !defined(PHOTO_REFLECTOR1_DECLARED)
#define PHOTO_REFLECTOR1_DECLARED
#define this_(name) PhotoReflector1_##name

#elif !defined(PHOTO_REFLECTOR2_DECLARED)
#define PHOTO_REFLECTOR2_DECLARED
#define this_(name) PhotoReflector2_##name

#elif !defined(PHOTO_REFLECTOR3_DECLARED)
#define PHOTO_REFLECTOR3_DECLARED
#define this_(name) PhotoReflector3_##name

#elif !defined(PHOTO_REFLECTOR4_DECLARED)
#define PHOTO_REFLECTOR4_DECLARED
#define this_(name) PhotoReflector4_##name

#elif !defined(PHOTO_REFLECTOR5_DECLARED)
#define PHOTO_REFLECTOR5_DECLARED
#define this_(name) PhotoReflector5_##name

#elif !defined(PHOTO_REFLECTOR6_DECLARED)
#define PHOTO_REFLECTOR6_DECLARED
#define this_(name) PhotoReflector6_##name

#elif !defined(PHOTO_REFLECTOR7_DECLARED)
#define PHOTO_REFLECTOR7_DECLARED
#define this_(name) PhotoReflector7_##name

#elif !defined(PHOTO_REFLECTOR8_DECLARED)
#define PHOTO_REFLECTOR8_DECLARED
#define this_(name) PhotoReflector8_##name

#elif !defined(PHOTO_REFLECTOR9_DECLARED)
#define PHOTO_REFLECTOR9_DECLARED
#define this_(name) PhotoReflector9_##name

#define EXIT_LOOP
#endif

static const struct LED* this_(led);
static const struct PhotoTransistor* this_(photoTr);

static int this_(read)() {
	this_(led)->turnOn();
	int positive = this_(photoTr)->read();
	this_(led)->turnOff();
	int negative = this_(photoTr)->read();
	int result = positive - negative;
	return result < 0 ? 0 : result;
}

static const struct PhotoReflector this_(instance) = {
	this_(read),
};

static const struct PhotoReflector* this_(constructor)(
		const struct LED* led,
		const struct PhotoTransistor* photoTr) {
	this_(led) = &LED_dummy;
	this_(photoTr) = &PhotoTransistor_dummy;
	this_(led) = led;
	this_(photoTr) = photoTr;
	return &this_(instance);
}

#undef this_

#if !defined(EXIT_LOOP)
#include "PhotoReflector.c"
#endif

