#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include <inttypes.h>
#include <vector>
#include "effect.h"

class LightManager {
private:
	// Singleton realization 
	LightManager();
	LightManager(const LightManager &);
	LightManager &operator=(LightManager &);

	std::vector<Effect *> effects_;
	uint16_t currentEffectIdx_ = 0;
	unsigned long lastCallTime_ = 0;
public:
	static LightManager *getInstance();
	void begin();
	void handle();
	Effect* getCurrectEffect();
	bool setCurrentEffect(uint16_t effect_id);
	CRGB& operator[](const unsigned int index);
	void addEffect(Effect *effect);
	CRGBArray<NUM_LEDS> leds;
};

#endif // LIGHTMANAGER_H
