#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>

enum EffectFlags{
	WITH_PALETTE = 0x01,
	WITH_COLORPICKER = 0x02
};

class Effect {
public:
	Effect(String effect_name, uint8_t default_brightness,
		uint8_t default_speed, uint8_t default_scale, uint8_t default_flags = 0) :
		name(effect_name), brightness(default_brightness), speed(default_speed),
		scale(default_scale), flags(default_flags) {}
	virtual void Run() = 0;
	String name;
	uint8_t brightness;
	uint8_t speed;
	uint8_t scale;
	uint8_t flags;
};

#endif // EFFECT_H
