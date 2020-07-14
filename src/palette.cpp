#include "ledcontroller.h"
#include "palette.h"

Palette::Palette(String palette_name, CRGBPalette16 pal) :
	name(palette_name), palette(pal) {
	LedController::getInstance()->addPalette(this);
}

// --- List of palettes ---
FL_PROGMEM Palette rainbowPalette("Rainbow", Rainbow_gp);
FL_PROGMEM Palette rainbowStripePalette("Rainbow Stripe", RainbowStripeColors_p);
FL_PROGMEM Palette cloudPalette("Cloud", CloudColors_p);
FL_PROGMEM Palette lavaPalette("Lava", LavaColors_p);
FL_PROGMEM Palette oceanPalette("Ocean", OceanColors_p);
FL_PROGMEM Palette forestPalette("Forest", ForestColors_p);
FL_PROGMEM Palette partyPalette("Party", PartyColors_p);
FL_PROGMEM Palette heatPalette("Heat", HeatColors_p);
