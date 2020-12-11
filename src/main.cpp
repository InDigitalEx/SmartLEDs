/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined ESP32
#include <WiFi.h>
#endif

#include "serialmanager.h"
#include "otaupdater.h"
#include "ledcontroller.h"
#include "web.h"

static OtaUpdater otaUpdater;
static SerialManager serial;
static LedController *ledController = LedController::getInstance();
static Web *web = Web::getInstance();

void setup() {
	// Init Serial
	serial.init(115200);

	// Init SFX
	ledController->init();
	
	// Init Wifi
	WiFi.begin("TP-Link_0A9A", "yGMau42i");
	while(WiFi.status() != WL_CONNECTED) {
		delay(100);
		Serial.print("*");
	}
	Serial.println();

	// Init web module
	web->init();

	// Init OTA
	otaUpdater.init(true);

	serial.printDebugInfo();
}

void loop() {
	randomSeed(micros());
	random16_add_entropy(random(0xFFFF));

	ledController->handle();
	web->handle();
	otaUpdater.handle();
	yield();

	#ifdef DEBUG
	Serial.println(FastLED.getFPS());
	#endif
}
