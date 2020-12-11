#ifndef SETTING_H
#define SETTING_H

#include <WString.h>
#include <inttypes.h>
#include "defines.h"

class Setting
{
private:
    String name_;
    uint8_t value_;
    uint8_t min_;
    uint8_t max_;
public:
    Setting(String name = "", uint8_t value = 0, uint8_t min = 0, uint8_t max = 255) : 
        name_(name), min_(min), max_(max) {
        set(value);
    }

    ALWAYS_INLINE uint8_t get() const {
        return value_;
    }

    ALWAYS_INLINE uint8_t operator()() const {
        return value_;
    }

    void set(uint8_t value) {
        value_ = constrain(value, min_, max_);
    }

    String& getName() {
        return name_;
    }

    ALWAYS_INLINE uint8_t getMinValue() const {
        return min_;
    }

    ALWAYS_INLINE uint8_t getMaxValue() const {
        return max_;
    }
};

#endif // SETTING_H
