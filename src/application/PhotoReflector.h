#ifndef PHOTO_REFLECTOR_H
#define PHOTO_REFLECTOR_H

struct PhotoReflector {
	int (*read)(void);
};

#endif /* PHOTO_REFLECTOR_H */
