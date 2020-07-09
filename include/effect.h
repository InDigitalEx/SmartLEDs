#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>
#include <WString.h>

class Effect {
public:
    Effect(String effect_name, uint8_t default_brightness, uint8_t default_speed, uint8_t default_scale) :
        name(effect_name), brightness(default_brightness), speed(default_speed), scale(default_scale) {}
    virtual void Run() = 0;
    String name;
    uint8_t brightness;
    uint8_t speed;
    uint8_t scale;
};

#endif // EFFECT_H
