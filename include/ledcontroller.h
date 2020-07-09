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
	Effect* currentEffect = nullptr;
	Palette* currentPalette = nullptr;
	Effect* getCurrentEffect();
	Palette* getCurrentPalette();
	bool setCurrentEffect(uint16_t effect_id);
	bool setCurrentPalette(uint16_t palette_id); 
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
	uint16_t currentEffectIdx_ = 0;
	uint16_t currentPaletteIdx = 0;
	uint32_t lastCallTime_ = 0;
};

#endif // LEDCONTROLLER_H
