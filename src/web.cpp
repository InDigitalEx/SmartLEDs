#include "web.h"
#include <WString.h>

Web* Web::getInstance() {
    static Web instance;
    return &instance;
}

Web::~Web() {
    delete json;
    delete udpSocket_;
}

void Web::init() {
    json = new JsonHandler();
    json->init();

    // Init UDP Socket
    udpSocket_ = new AsyncUDP();
    if(udpSocket_->listen(UDP_PORT)) {
        udpSocket_->onPacket([&](const AsyncUDPPacket &packet) {
            // Light music implementation
        });
    }
}

void Web::handle() {
}
