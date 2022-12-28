#include "ledcontroller.h"
#include "effect.h"

static LedController* controller = LedController::getInstance();
static Manager<Effect>* effects = controller->getEffects();
static CRGB* leds = controller->getLeds();
static CRGBPalette16* blendPalette = controller->getBlendPalette();

// Effects
class Fire : public Effect {
private:
	Setting flameHeight_{"Высота пламени", 55, 20, 100};
	Setting sparking_{"Искры", 120, 50, 200};
public:
	Fire() : Effect("Огонь", MODE_STANDARD | MODE_PALETTE, {&flameHeight_, &sparking_}) {
		effects->add(this);
	}
	void Run() override final {
		static byte heat[NUM_LEDS];

		// Cool down every cell a little
		for(int i = 0; i < NUM_LEDS; i++) {
			heat[i] = qsub8(heat[i],  random8(0, ((flameHeight_() * 10) / NUM_LEDS) + 2));
		}
	
		// Heat from each cell drifts 'up' and diffuses a little
		for(int k = NUM_LEDS - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		
		// Randomly ignite new 'sparks' of heat near the bottom
		if(random8() < sparking_()) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160,255));
		}

		// Draw to leds
		if(IS_MOD_ENABLED(MODE_STANDARD)) {
			for(int j = 0; j < NUM_LEDS; j++) {
				leds[j] = HeatColor(heat[j]);
			}
		}
		else if(IS_MOD_ENABLED(MODE_PALETTE)) {
			for(int j = 0; j < NUM_LEDS; j++) {
				byte colorindex = scale8(heat[j], 240);
				leds[j] = ColorFromPalette(*blendPalette, colorindex);
			}
		}
	}
} fireEffect;

class Rainbow : public Effect {
public:
	Rainbow() : Effect("Радуга", MODE_STANDARD) {
		effects->add(this);
	};
	void Run() override final {
		static uint16_t sPseudotime = 0;
		static uint16_t sLastMillis = 0;
		static uint16_t sHue16 = 0;

		uint8_t sat8 = beatsin88(87, 220, 250);
		uint8_t brightdepth = beatsin88(341, 96, 224);
		uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
		uint8_t msmultiplier = beatsin88(147, 23, 60);

		uint16_t hue16 = sHue16;
		uint16_t hueinc16 = beatsin88(113, 1, 3000);

		uint16_t ms = millis();
		uint16_t deltams = ms - sLastMillis;
		sLastMillis = ms;
		sPseudotime += deltams * msmultiplier;
		sHue16 += deltams * beatsin88(400, 5, 9);
		uint16_t brightnesstheta16 = sPseudotime;

		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			hue16 += hueinc16;
			uint8_t hue8 = hue16 / 256;

			brightnesstheta16 += brightnessthetainc16;
			uint16_t b16 = sin16(brightnesstheta16) + 32768;

			uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
			uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
			bri8 += (255 - brightdepth);

			CRGB newcolor = CHSV(hue8, sat8, bri8);

			uint16_t pixelnumber = i;
			pixelnumber = (NUM_LEDS - 1) - pixelnumber;
			nblend(leds[pixelnumber], COLOR(newcolor), 64);
		}
	}
} rainbowEffect;
