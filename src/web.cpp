#include "web.h"
#include <WString.h>

Web* Web::getInstance() {
    static Web instance;
    return &instance;
}

void Web::init() {
    json = new JsonHandler();
    json->init();

    udpSocket_ = new AsyncUDP();
    if(udpSocket_->listen(UDP_PORT)) {
        udpSocket_->onPacket([&](AsyncUDPPacket packet) {
            // Light music implementation
        });
    }

    webSocket_ = new WebSocketsServer(81);
    webSocket_->begin();
    webSocket_->onEvent([&](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
        switch (type)
        {
        case WStype_CONNECTED: {
            String buffer;
            json->generateJsonList(buffer);
            webSocket_->sendTXT(num, buffer);
            break;
        }
        case WStype_DISCONNECTED: {
            break;
        }
        case WStype_TEXT: {
            json->handleIncomingText(payload);
            break; 
        }
        case WStype_ERROR: {
            break;
        }
        default: {
            break;
        }
        }
    });
}

void Web::handle() {
}
