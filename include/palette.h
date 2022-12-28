#ifndef PALETTE_H
#define PALETTE_H

#include <inttypes.h>
#include <WString.h>
#include "ledcontroller.h"

const unsigned int PALETTE_OBJECTS = 1;

class Palette {
private:
	String name_;
	CRGBPalette16 palette_;
public:
	Palette(String palette_name, CRGBPalette16 pal);

	inline String& getName() {
		return name_;
	}

	inline CRGBPalette16& getPalette() {
		return palette_;
	}
};

#endif // PALETTE_H
