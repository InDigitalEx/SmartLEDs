#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include <inttypes.h>
#include <vector>
#include "effect.h"
#include "palette.h"

class LedController {
public:
	static LedController *getInstance();
	void init();
	void handle();
	Effect* getCurrentEffect();
	Palette* getCurrentPalette();
	void setCurrentEffect(uint8_t effect_id);
	void setCurrentPalette(uint8_t palette_id);
	void addEffect(Effect *effect);
	void addPalette(Palette *palette);
	CRGB* getLeds();

private:
	// Singleton realization
	LedController() = default;
	LedController(const LedController &) = delete;
	LedController &operator=(LedController &) = delete;

	CRGB leds_[NUM_LEDS];
	std::vector<Effect *> effects_;
	std::vector<Palette *> palettes_;
	uint8_t currentEffectIdx_ = 0;
	uint8_t currentPaletteIdx_ = 0;
	uint32_t lastCallTime_ = 0;
};

#endif // LEDCONTROLLER_H
