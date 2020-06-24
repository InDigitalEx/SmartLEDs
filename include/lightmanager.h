#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_INTERRUPT_RETRY_COUNT 0

#include <inttypes.h>
#include <vector>
#include <FastLED.h>
#include "effect.h"

class LightManager {
	private:
	// Singleton realization 
	LightManager() { }
	LightManager(const LightManager &);
	LightManager &operator=(LightManager &);
	// ~~~~~~~~~~~~~~~~~
	std::vector<Effect*> childrens_;
	uint16_t currentIdx_ = 0;

	public:
	// Singleton realization
	static LightManager *getInstance()
	{
		static LightManager instance;
		return &instance;
	}
	// ~~~~~~~~~~~~~~~~~
	CRGB leds[NUM_LEDS];
	void begin();
	void handle();
	Effect* getCurrectEffect();
	bool setCurrentEffect(uint16_t effect_id);
	CRGB& operator[](const unsigned int index);
	void add(Effect *effect);
	LightManager* operator+=(Effect *right);
};

#endif // LIGHTMANAGER_H