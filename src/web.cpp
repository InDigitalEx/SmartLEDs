#include "web.h"

Web* Web::getInstance() {
    static Web instance;
    return &instance;
}

void Web::init() {
    json.init();
    if(udpSocket_.listen(UDP_PORT)) {
        udpSocket_.onPacket([&](AsyncUDPPacket packet) {
            // Light music implementation
        });
    }
}

void Web::handle() {
}
