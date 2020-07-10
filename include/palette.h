#ifndef PALETTE_H
#define PALETTE_H

#include <inttypes.h>
#include <WString.h>
#include "ledcontroller.h"

class Palette {
public:
	Palette(String palette_name, CRGBPalette16 pal);
	String name;
	CRGBPalette16 palette;
};

#endif // PALETTE_H
