#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <WString.h>

class JsonHandler
{
public:
    void init();
    void generateJson(String& destination);
    void handleIncomingText(unsigned char* text);
};

#endif // JSONHANDLER_H