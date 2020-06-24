#ifndef SFX_H
#define SFX_H

#include <Arduino.h>
#include <inttypes.h>
#include "effect.h"
#include "lightmanager.h"

class Rainbow : public Effect {
	private:
		byte counter = 0;
		unsigned long lastTime = 0;
		LightManager *lights = LightManager::getInstance();

	public:
		Rainbow() {
			this->speed = 50;
			this->scale = 2;
			LightManager::getInstance()->add(this);
		}
		void Run() {
			if(millis() - lastTime > lights->getCurrectEffect()->speed)
			{
				lastTime = millis();
				for (int i = 0; i < NUM_LEDS; i++)
				{
					LightManager::getInstance()->leds[i] = CHSV(
						counter + i * lights->getCurrectEffect()->scale, 255, 255);
				}
				counter++;
			}
			FastLED.show();
		}
} rainbowFx;

#endif // SFX_H