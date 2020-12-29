#include "web.h"
#include <WString.h>
#include <functional>

Web* Web::getInstance() {
    static Web instance;
    return &instance;
}

Web::~Web() {
    delete json_;
    delete udpSocket_;
    delete server_;
    delete webSocket_;
}

void Web::init() {
    json_ = new JsonHandler();
    json_->init();

    // Init UDP Socket
    udpSocket_ = new AsyncUDP();
    if(udpSocket_->listen(UDP_PORT)) {
        udpSocket_->onPacket([&](const AsyncUDPPacket &packet) {
            // Light music implementation
        });
    }

    server_ = new AsyncWebServer(80);
    server_->on("/", HTTP_GET, std::bind(&Web::onServerRootEvent, this, std::placeholders::_1));
    server_->on("/heap", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });

    webSocket_ = new AsyncWebSocket("/ws");
    webSocket_->onEvent(std::bind(&Web::onWebSocketEvent, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));

    server_->addHandler(webSocket_);
    server_->begin();
}

void Web::handle() {
}

void Web::onServerRootEvent(AsyncWebServerRequest *request) {

}

void Web::onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type,
    void * arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT: {
            Serial.printf("WebSocket client #%u connected from %s\n",
                client->id(), client->remoteIP().toString().c_str());
            String *tmp = new String();

            json_->generateJson(*tmp);
            client->text(*tmp);
            delete tmp;

            break;
        }
        case WS_EVT_DISCONNECT: {
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        }
        case WS_EVT_DATA: {
            AwsFrameInfo *info = (AwsFrameInfo*)arg;
            if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
                data[len] = 0;
                json_->handleIncomingText((char*)data);
            }
            break;
        }
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
        break;
    }
}