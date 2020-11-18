#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <WString.h>

class JsonHandler
{
private:
    uint16_t maxJsonListLength_;
public:
    void init();
    void generateJsonList(String& destination);
    void handleIncomingText(uint8_t* payload);
};

#endif // JSONHANDLER_H