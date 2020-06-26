#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>

class SerialManager {
public:
    void begin(unsigned long baud);
    void printDebug();
};

#endif // SERIALMANAGER_H
