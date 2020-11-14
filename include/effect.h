#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>

const uint8_t EFFECT_OBJECTS = 5;

class Effect {
public:
	Effect(
		String effect_name = "Безымянный"
		, uint8_t default_speed = 10
		, uint8_t default_scale = 1
		, uint8_t default_flags = 0x0
		, uint8_t default_brightness = 255) :
		name_(effect_name)
		, speed_(default_speed)
		, scale_(default_scale)
		, flags_(default_flags)
		, brightness_(default_brightness) {
	}

	// Virtual function for effect
	virtual void Run() = 0;

	// Name
	inline String& getName() {
		return name_;
	}
	
	inline void setName(String name) {
		name_ = name;
	}

	// Speed
	inline uint8_t getSpeed() {
		return speed_;
	}

	inline void setSpeed(uint8_t speed) {
		speed_ = speed;
	}

	// Scale
	inline uint8_t getScale() {
		return scale_;
	}

	inline void setScale(uint8_t scale) {
		scale_ = scale;
	}
	
	inline uint8_t getFlags() {
		return flags_;
	}

	inline void setFlags(uint8_t flags) {
		flags_ = flags;
	}

	// Brightness
	inline uint8_t getBrightness() {
		return brightness_;
	}

	inline void setBrightness(uint8_t brightness) {
		brightness_ = brightness;
	}

	enum Modes {
		HAS_PALETTE = 0x01,
		HAS_COLORPICKER = 0x02
	};
private:
	String name_;
	uint8_t speed_;
	uint8_t scale_;
	uint8_t flags_;
	uint8_t brightness_;
};

#endif // EFFECT_H
