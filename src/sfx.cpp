#include "ledcontroller.h"
#include "effect.h"

LedController *controller = LedController::getInstance();
CRGB *leds = controller->getLeds();

// Effects
class PaletteViewer : public Effect {
public:
	PaletteViewer() : Effect(F("Просмотр палитр"), 255, 255, 2, WITH_PALETTE) {
		controller->addEffect(this);
	};
	void Run() {
		EVERY_N_SECONDS(5) {
			static size_t i;
			if(++i >= controller->getPalettesArray()->size()) i = 0;
			controller->setCurrentPalette(i);
		}
		fill_palette(leds, NUM_LEDS, 0, scale,
			controller->getCurrentPalette()->palette, brightness, LINEARBLEND);
	}
} paletteViewer;
