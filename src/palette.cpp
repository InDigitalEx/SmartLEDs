#include "ledcontroller.h"
#include "palette.h"

Palette::Palette(String palette_name, CRGBPalette16 pal) :
	name_(palette_name), palette_(pal) {
	LedController::getInstance()->getPalettes()->add(this);
}

// --- List of palettes ---
Palette *rainbowPalette			= new Palette("Rainbow", Rainbow_gp);
Palette *rainbowStripePalette	= new Palette("Rainbow Stripe", RainbowStripeColors_p);
Palette *cloudPalette			= new Palette("Cloud", CloudColors_p);
Palette *lavaPalette			= new Palette("Lava", LavaColors_p);
Palette *oceanPalette			= new Palette("Ocean", OceanColors_p);
Palette *forestPalette			= new Palette("Forest", ForestColors_p);
Palette *partyPalette			= new Palette("Party", PartyColors_p);
Palette *heatPalette			= new Palette("Heat", HeatColors_p);
