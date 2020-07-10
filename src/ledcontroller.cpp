#include "ledcontroller.h"

LedController* LedController::getInstance() {
	static LedController instance;
	return &instance;
}

void LedController::init() {
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds_, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setDither(true);
	FastLED.setBrightness(0);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);
	fill_solid(leds_, NUM_LEDS, CRGB::Black);
	FastLED.show();

	// Set default current values
	setCurrentEffect(0);
	setCurrentPalette(0);
}

void LedController::handle() {
	if(millis() - lastCallTime_ > getCurrentEffect()->speed) {
		lastCallTime_ = millis();
		getCurrentEffect()->Run();
	}
	FastLED.delay(1000 / UPDATES_PER_SECOND);
}

Effect *LedController::getCurrentEffect() {
	if(effects_.size() == 0)
		return nullptr;

	return effects_[currentEffectIdx_];
}

Palette *LedController::getCurrentPalette() {
	if(palettes_.size() == 0)
		return nullptr;

	return palettes_[currentPaletteIdx_];
}

void LedController::setCurrentEffect(uint8_t effect_id) {
	currentEffectIdx_ = effect_id >= effects_.size() ? effects_.size() - 1 : effect_id;
}

void LedController::setCurrentPalette(uint8_t palette_id) {
	currentPaletteIdx_ = palette_id >= palettes_.size() ? palettes_.size() - 1 : palette_id;
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
