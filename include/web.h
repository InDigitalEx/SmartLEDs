#ifndef WEB_H
#define WEB_H


#ifdef ESP8266
#include <ESPAsyncUDP.h>
#elif defined(ESP32)
#include <Arduino.h>
#include <AsyncUDP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include "jsonhandler.h"

const unsigned int UDP_PORT = 8780;

class Web {
public:
    static Web *getInstance();
	~Web();

	void init();
	void handle();

	inline JsonHandler* getJson() { return json_; }

	// Event handlers
	void onServerRootEvent(AsyncWebServerRequest *request);
	void onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client,
		AwsEventType type, void * arg, uint8_t *data, size_t len);
private:
	JsonHandler *json_;
	AsyncUDP *udpSocket_;
	AsyncWebServer *server_;
	AsyncWebSocket *webSocket_;

	// Singleton realization
	Web() = default;
	Web(const Web &) = delete;
	Web &operator=(Web &) = delete;
};

#endif // WEBSOCKET_H