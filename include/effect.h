#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>
#include <vector>
#include "leds/setting.h"

#define IS_MOD_ENABLED(value)	(mode()->get() & (value))
#define COLOR(value)			IS_MOD_ENABLED(MODE_STANDARD) ? \
								value : ColorFromPalette(*blendPalette, value)

class Effect {
public:
	Effect(String name, uint8_t available_modes = MODE_STANDARD,
		std::initializer_list<Setting*> l = {}) : name_(name), settings_(l) {
		availableModes_.set(available_modes);

		// check max effects
		uint8_t bit = 1;
		while(bit <= available_modes) {
			if(available_modes & bit) {
				currentMode_.set(bit);
				break;
			}
			bit *= 2;
		}
	}

	// Virtual function for effect
	virtual void Run() = 0;

	// Name
	inline String& name() {
		return name_;
	}

	// Brightness
	inline Setting* brightness() {
		return &brightness_;
	}

	// Modes
	inline Setting* availableModes() {
		return &availableModes_;
	}

	inline Setting* mode() {
		return &currentMode_;
	}

	enum Modes {
		MODE_STANDARD		= 0b0001,
		MODE_PALETTE		= 0b0010,
		MODE_COLORPICKER	= 0b0100,
		MODE_LIGHTMUSIC		= 0b1000
	};
	
	// Settings
	inline std::vector<Setting*>* settings() {
		return &settings_;
	}

	void addSetting(Setting* setting) {
		settings_.push_back(setting);
	}
private:
	String name_;
	Setting brightness_{"", 255};
	Setting availableModes_{"", MODE_STANDARD};
	Setting currentMode_{"", MODE_STANDARD};
	std::vector<Setting*> settings_;
};

#endif // EFFECT_H
