#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>

const uint8_t EFFECT_OBJECTS = 5;

class Effect {
public:
	Effect(String name, uint8_t speed = 8, uint8_t scale = 1,
		uint8_t params = 0, uint8_t brightness = 255) :
		name_(name), speed_(speed), scale_(scale),
		params_(params), brightness_(brightness) {
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
	inline uint8_t getSpeed() const {
		return speed_;
	}

	inline void setSpeed(uint8_t speed) {
		speed_ = speed;
	}

	// Scale
	inline uint8_t getScale() const {
		return scale_;
	}

	inline void setScale(uint8_t scale) {
		scale_ = scale;
	}
	
	inline uint8_t getParams() const {
		return params_;
	}

	inline void setParams(uint8_t params) {
		params_ = params;
	}

	// Brightness
	inline uint8_t getBrightness() const {
		return brightness_;
	}

	inline void setBrightness(uint8_t brightness) {
		brightness_ = brightness;
	}

	// Mode
	inline uint8_t getMode() const {
		return mode_;
	}

	inline void setMode(uint8_t mode) {
		mode_ = mode;
	}
	
	enum Params {
		PARAM_NONE = 0x0,
		PARAM_COLORPICKER = 0x02,
		PARAM_PALETTE = 0x01
	};

	enum Modes {
		MODE_COLORPICKER,
		MODE_PALETTE,
		MODE_LIGHTMUSIC
	};
private:
	String name_;
	uint8_t speed_;
	uint8_t scale_;
	uint8_t params_;
	uint8_t brightness_;
	uint8_t mode_ = 0;
};

#endif // EFFECT_H
