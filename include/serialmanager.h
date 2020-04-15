#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

class SerialManager {
    public:
        void begin(unsigned long baud);
        void printDebug();
};

#endif // SERIALMANAGER_H