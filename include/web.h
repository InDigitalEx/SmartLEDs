#ifndef WEB_H
#define WEB_H

#include <ESPAsyncUDP.h>
#include "jsonhandler.h"
#include "defines.h"

const unsigned int UDP_PORT = 8780;

class Web {
public:
    static Web *getInstance();
	~Web();

	void init();
	void handle();
	ALWAYS_INLINE JsonHandler* getJson() {
		return json;
	}
private:
	JsonHandler *json;
	AsyncUDP *udpSocket_;

	// Singleton realization
	Web() = default;
	Web(const Web &) = delete;
	Web &operator=(Web &) = delete;
};

#endif // WEBSOCKET_H