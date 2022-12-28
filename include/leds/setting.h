#ifndef SETTING_H
#define SETTING_H

#include <WString.h>
#include <inttypes.h>

typedef uint16_t SettingValue;

class Setting
{
private:
    String name_;
    SettingValue value_;
    SettingValue min_;
    SettingValue max_;
public:
    Setting(String name = "", SettingValue value = 0, SettingValue min = 0, SettingValue max = 255) : 
        name_(name), min_(min), max_(max) {
        set(value);
    }

    inline SettingValue get() const {
        return value_;
    }

    inline SettingValue operator()() const {
        return value_;
    }

    void set(SettingValue value) {
        value_ = constrain(value, min_, max_);
    }

    String& getName() {
        return name_;
    }

    inline SettingValue getMinValue() const {
        return min_;
    }

    inline SettingValue getMaxValue() const {
        return max_;
    }
};

#endif // SETTING_H
