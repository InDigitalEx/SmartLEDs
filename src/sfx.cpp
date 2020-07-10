#include "ledcontroller.h"
#include "effect.h"

LedController *controller = LedController::getInstance();
CRGB *leds = controller->getLeds();

// Effects
class PaletteViewer : public Effect {
public:
	PaletteViewer() : Effect(F("Просмотр палитр"), 128, 10, 0) {
		controller->addEffect(this);
	};
	void Run() {
		static uint8_t startindex = 0;
		startindex--;
		fill_palette(leds, NUM_LEDS, startindex, (256 / NUM_LEDS) + 1,
			controller->getCurrentPalette()->palette, brightness, LINEARBLEND);
	}
} paletteViewer;
