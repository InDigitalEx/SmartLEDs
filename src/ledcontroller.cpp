#include "ledcontroller.h"

LedController* LedController::getInstance() {
	static LedController instance;
	return &instance;
}

void LedController::init() {
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds_, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(128);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);
	FastLED.setDither(true);
	
	// Fill all strip
	for(int i = 0; i < NUM_LEDS; i++) {
		leds_[i] = CRGB::Black;
	}
	FastLED.show();

	// Set default current values
	currentEffect = effects_[currentEffectIdx_];
	currentPalette = palettes_[currentPaletteIdx];
}

void LedController::handle() {
	if(millis() - lastCallTime_ > currentEffect->speed) {
		lastCallTime_ = millis();
		currentEffect->Run();
	}
	FastLED.delay(1000 / UPDATES_PER_SECOND);
}

Effect *LedController::getCurrentEffect() {
	if(effects_.size() == 0)
		return nullptr;

	return effects_[currentEffectIdx_];
}

Palette *LedController::getCurrentPalette() {
	if (palettes_.size() == 0)
		return nullptr;

	return palettes_[currentPaletteIdx];
}

bool LedController::setCurrentEffect(uint16_t effect_id) {
	if(effect_id > effects_.size())
		return false;
	
	currentEffectIdx_ = effect_id;
	currentEffect = effects_[currentEffectIdx_];
	return true;
}

bool LedController::setCurrentPalette(uint16_t palette_id) {
	if (palette_id > palettes_.size())
		return false;
	
	currentPaletteIdx = palette_id;
	currentPalette = palettes_[currentPaletteIdx];
	return true;
}

void LedController::addEffect(Effect *effect) {
	effects_.push_back(effect);
}

void LedController::addPalette(Palette *palette) {
	palettes_.push_back(palette);
}

CRGB* LedController::getLeds() {
	return leds_;
}
