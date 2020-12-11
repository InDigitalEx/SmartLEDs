#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>
#include <inttypes.h>
#include "effect.h"
#include "palette.h"
#include "leds/manager.h"
#include "defines.h"

class LedController {
public:
	static LedController *getInstance();

	void init();
	void handle();

	CRGB* getLeds();
	ALWAYS_INLINE Manager<Effect>* getEffects() { return &effects_; }
	ALWAYS_INLINE Manager<Palette>* getPalettes() { return &palettes_; }
	ALWAYS_INLINE CRGBPalette16& getBlendPalette() { return blendPalette_; }

	ALWAYS_INLINE bool getPower() const { return power_; }
	void setPower(bool status);
private:
	// Singleton realization
	LedController() = default;
	LedController(const LedController &) = delete;
	LedController &operator=(LedController &) = delete;

	Manager<Effect> effects_;
	Manager<Palette> palettes_;
	CRGBPalette16 blendPalette_;
	CRGB leds_[NUM_LEDS];

	bool power_ = true;
};

#endif // LEDCONTROLLER_H
