#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>
#include "leds/setting.h"
#include "defines.h"

#define IS_MOD_ENABLED(value)	(mode()->get() & (value))

class Effect {
public:
	Effect(String name, uint8_t available_modes = MODE_STANDARD,
		std::initializer_list<Setting*> l = {}) : name_(name), settings_(l) {
		availableModes_.set(available_modes);
	}

	// Virtual function for effect
	virtual void Run() = 0;

	// Name
	ALWAYS_INLINE String& name() {
		return name_;
	}

	// Brightness
	ALWAYS_INLINE Setting* brightness() {
		return &brightness_;
	}

	// Modes
	ALWAYS_INLINE Setting* availableModes() {
		return &availableModes_;
	}

	ALWAYS_INLINE Setting* mode() {
		return &mode_;
	}

	enum Modes {
		MODE_STANDARD		= 0b0001,
		MODE_PALETTE		= 0b0010,
		MODE_COLORPICKER	= 0b0100,
		MODE_LIGHTMUSIC		= 0b1000
	};
	
	// Settings
	ALWAYS_INLINE std::vector<Setting*>* settings() {
		return &settings_;
	}

	void addSetting(Setting& setting) {
		settings_.push_back(&setting);
	}
private:
	String name_;
	Setting brightness_{"", 255};
	Setting availableModes_;
	Setting mode_;
	std::vector<Setting*> settings_;
};

#endif // EFFECT_H
