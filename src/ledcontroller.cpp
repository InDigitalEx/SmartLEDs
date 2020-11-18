#include "ledcontroller.h"

LedController* LedController::getInstance() {
	static LedController instance;
	return &instance;
}

void LedController::init() {
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds_, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setDither(false);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);
	fill_solid(leds_, NUM_LEDS, CRGB::Black);
	FastLED.show();
}

void LedController::handle() {
	Effect *effect = getCurrentEffect();

	if(!power_) {
		for(int i = 0; i < NUM_LEDS; i++) {
			nblend(leds_[i], CRGB::Black, 24);
		}
	} 
	else {
		nblendPaletteTowardPalette(palette_, palettes_[currentPaletteIdx_]->palette, 24);

		if (millis() - lastCallTime_ >= effect->getSpeed()) {
			lastCallTime_ = millis();
			effect->Run();
		}
	}

	FastLED.setBrightness(effect->getBrightness());
	FastLED.show();
	FastLED.delay(1000 / UPDATES_PER_SECOND);
}

Effect *LedController::getCurrentEffect() {
	if(effects_.size() == 0)
		return nullptr;

	return effects_[currentEffectIdx_];
}

CRGBPalette16 &LedController::getCurrentPalette() {
	return palette_;
}

void LedController::getCurrentPalette(Palette& palette) {
	palette.name = palettes_[currentPaletteIdx_]->name;
	palette.palette = palette_;
}

String &LedController::getCurrentPaletteName() {
	return palettes_[currentPaletteIdx_]->name;
}

void LedController::setCurrentEffect(uint8_t effect_id) {
	lastCallTime_ = 0;
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

std::vector<Effect *>* LedController::getVectorOfEffects() {
	return &effects_;
}

std::vector<Palette *>* LedController::getVectorOfPalettes() {
	return &palettes_;
}

CRGB* LedController::getLeds() {
	return leds_;
}

uint8_t LedController::getMode() {
	return mode_;
}

void LedController::setPower(bool status) {
	lastCallTime_ = 0;
	power_ = status;
}

void LedController::setSpeed(uint8_t value) {
	getCurrentEffect()->setSpeed(value);
}

void LedController::setScale(uint8_t value) {
	getCurrentEffect()->setScale(value);
}

void LedController::setBrightness(uint8_t value) {
	getCurrentEffect()->setBrightness(value);
}

void LedController::setMode(uint8_t value) {
	mode_ = value;
}
