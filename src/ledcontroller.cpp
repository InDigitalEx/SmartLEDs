#include "ledcontroller.h"

LedController* LedController::getInstance() {
	static LedController instance;
	return &instance;
}

void LedController::init() {
	pinMode(LED_BUILTIN, OUTPUT);

	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds_, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setDither(false);

	set_max_power_indicator_LED(LED_BUILTIN);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_SUPPLY_AMPERAGE);

	fill_solid(leds_, NUM_LEDS, CRGB::Black);
	FastLED.show();
}

void LedController::handle() {
	Effect *effect = getEffects()->getCurrent();

	if(!power_) {
		for(int i = 0; i < NUM_LEDS; i++) {
			nblend(leds_[i], CRGB::Black, 24);
		}
	}
	else {
		nblendPaletteTowardPalette(blendPalette_, getPalettes()->getCurrent()->getPalette(), 24);
		effect->Run();
	}

	FastLED.setBrightness(effect->brightness()->get());
	FastLED.show();
	//FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void LedController::setPower(bool status) {
	power_ = status;
}
