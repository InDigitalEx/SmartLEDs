#include "sfx.h"

LightManager *light = LightManager::getInstance();

// Effects
class Rainbow : public Effect {
private:
	byte counter = 0;

public:
	Rainbow() {
		this->speed = 50;
		this->scale = 2;
		light->addEffect(this);
	}
	void Run() {
		for (int i = 0; i < NUM_LEDS; i++) {
			light->leds[i] = CHSV(counter + i * light->getCurrectEffect()->scale, 255, 255);
		}
		counter++;
	}
} rainbowFx;
