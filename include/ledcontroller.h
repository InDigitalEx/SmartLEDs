#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>
#include <inttypes.h>
#include "effect.h"
#include "palette.h"
#include "leds/manager.h"

class LedController {
public:
	static LedController *getInstance();

	void init();
	void handle();

	inline CRGB* getLeds() { return leds_; }
	inline Manager<Effect>* getEffects() { return &effects_; }
	inline Manager<Palette>* getPalettes() { return &palettes_; }
	inline CRGBPalette16* getBlendPalette() { return &blendPalette_; }

	inline bool getPower() const { return power_; }
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
