#ifndef OTAHANDLER_H
#define OTAHANDLER_H

#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

class OtaHandler {
public:
	void begin(bool rebootOnSuccess);
	void handle();
};

#endif // OTAHANDLER_H
