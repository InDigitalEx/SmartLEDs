#include "lightmanager.h"

LightManager::LightManager() {

}

LightManager* LightManager::getInstance() {
	static LightManager instance;
	return &instance;
}

void LightManager::begin() {
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(128);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);
	FastLED.setDither(true);
	
	// Fill all strip
	for(int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void LightManager::handle() {
	if(millis() - lastCallTime_ > getCurrectEffect()->speed) {
		lastCallTime_ = millis();
		getCurrectEffect()->Run();
	}
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}

Effect* LightManager::getCurrectEffect() {
	if(effects_.size() == 0) {
		return nullptr;
	}
	return effects_[currentEffectIdx_];
}

bool LightManager::setCurrentEffect(uint16_t effect_id) {
	if(effect_id > effects_.size()) {
		return false;
	}
	currentEffectIdx_ = effect_id;
	return true;
}

CRGB& LightManager::operator[](const unsigned int index) {
	return leds[index];
}

void LightManager::addEffect(Effect *effect) {
	effects_.push_back(effect);
}
