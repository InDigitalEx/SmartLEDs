#ifndef WEB_H
#define WEB_H

#include <Arduino.h>
#include <ESPAsyncUDP.h>
#include "jsonhandler.h"


const unsigned int UDP_PORT = 8780;

class Web {
public:
    static Web *getInstance();

	void init();
	void handle();
private:
	JsonHandler json;
	AsyncUDP udpSocket_;

	// Singleton realization
	Web() = default;
	Web(const Web &) = delete;
	Web &operator=(Web &) = delete;
};

#endif // WEBSOCKET_H