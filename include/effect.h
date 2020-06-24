#ifndef EFFECT_H
#define EFFECT_H

#include <inttypes.h>

class Effect {
public:
    virtual void Run() = 0;
    uint8_t brightness;
    uint8_t speed;
    uint8_t scale;
};

#endif // EFFECT_H
