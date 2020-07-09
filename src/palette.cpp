#include "ledcontroller.h"
#include "palette.h"

Palette::Palette(String palette_name, CRGBPalette16 pal) :
    name(palette_name), palette(pal) {
    LedController::getInstance()->addPalette(this);
}

// --- List of palettes ---
DEFINE_GRADIENT_PALETTE(Retro_p) {
    0,      188,    135,    1,
    255,    46,     7,      1
};

Palette partyPalette("Party", PartyColors_p);
Palette retroPalette("Retro", Retro_p);
