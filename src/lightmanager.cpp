#include "lightmanager.h"

void LightManager::begin() {
	// Init fastled
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(this->leds, NUM_LEDS);
	FastLED.setDither(false);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(40);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);

	// Fill all strip
	for(int i = 0; i < NUM_LEDS; i++) {
		this->leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void LightManager::handle() {
	this->getCurrectEffect()->Run();
	FastLED.show();
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}

Effect* LightManager::getCurrectEffect() {
	if(this->childrens_.size() == 0) {
		return nullptr;
	}
	return this->childrens_[this->currentIdx_];
}

bool LightManager::setCurrentEffect(uint16_t effect_id) {
	if(effect_id > this->childrens_.size()) {
		return false;
	}
	this->currentIdx_ = effect_id;
	return true;
}

CRGB& LightManager::operator[](const unsigned int index) {
	return this->leds[index];
}

void LightManager::add(Effect *effect) {
	this->childrens_.push_back(effect);
}

LightManager* LightManager::operator+=(Effect *right) {
	this->childrens_.push_back(right);
	return this;
}
