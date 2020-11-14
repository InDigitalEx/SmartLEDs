#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#define FASTLED_INTERRUPT_RETRY_COUNT 0
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
	CRGBPalette16& getCurrentPalette();

	void getCurrentPalette(Palette& palette);
	String& getCurrentPaletteName();

	void setCurrentEffect(uint8_t effect_id);
	void setCurrentPalette(uint8_t palette_id);

	void addEffect(Effect *effect);
	void addPalette(Palette *palette);
	
	std::vector<Effect *>* getVectorOfEffects();
	std::vector<Palette *>* getVectorOfPalettes();
	CRGB* getLeds();

	void setPower(bool status);
	void setSpeed(uint8_t value);
	void setScale(uint8_t value);
	void setBrightness(uint8_t value);
private:
	// Singleton realization
	LedController() = default;
	LedController(const LedController &) = delete;
	LedController &operator=(LedController &) = delete;

	std::vector<Effect *> effects_;
	std::vector<Palette *> palettes_;
	CRGBPalette16 palette_;
	CRGB leds_[NUM_LEDS];

	uint8_t currentEffectIdx_ = 0;
	uint8_t currentPaletteIdx_ = 0;
	uint32_t lastCallTime_ = 0;

	bool power_ = true;
	uint8_t mode_ = 0;
};

#endif // LEDCONTROLLER_H
