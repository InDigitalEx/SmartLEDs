/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

#include <WiFiManager.h>
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
	while(!Serial) continue;

	// Init SFX
	ledController->init();
	
	// Init Wifi connection manager
	WiFiManager wifiManager;
	wifiManager.autoConnect();
	#ifdef DEBUG
	wifiManager.setDebugOutput(true);
	#endif
	WiFi.setSleepMode(WIFI_NONE_SLEEP);

	// Init web module
	web->init();

	// Init OTA
	otaUpdater.init(true);

	serial.printDebugInfo();
}

void loop() {
	randomSeed(micros());
	random16_add_entropy(random(0xFFFF));

	ledController->setCurrentEffect(1);
	ledController->handle();
	web->handle();
	otaUpdater.handle();
	yield();
}
