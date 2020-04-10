#ifndef SERIALMANAGER_H_
#define SERIALMANAGER_H_

class SerialManager {
    public:
        void begin(unsigned long baud);
        void printDebug();
};

#endif // SERIALMANAGER_H_