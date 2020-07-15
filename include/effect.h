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
	Effect(String effect_name = "Безымянный",
	uint8_t default_speed = 10, uint8_t default_scale = 1,
	uint8_t default_flags = 0, uint8_t default_brightness = 255) : 
	name(effect_name), speed(default_speed), scale(default_scale),
	flags(default_flags), brightness(default_brightness) {}
	virtual void Run() = 0;
	String name;
	uint8_t speed;
	uint8_t scale;
	uint8_t flags;
	uint8_t brightness;
};

#endif // EFFECT_H
