/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

#include <WiFiManager.h>
#include "serialmanager.h"
#include "otaupdater.h"
#include "ledcontroller.h"

OtaUpdater otaUpdater;
SerialManager serial;

void setup() {
	// Init Serial
	serial.init(115200);
	
	// Init OTA
	otaUpdater.init(true);

	// Init SFX
	LedController::getInstance()->init();

	// Init Wifi connection manager
	WiFiManager wifiManager;
	wifiManager.autoConnect();
	#ifdef DEBUG
	wifiManager.setDebugOutput(true);
	#endif
	WiFi.setSleepMode(WIFI_NONE_SLEEP);

	serial.printDebugInfo();
}

void loop() {
	otaUpdater.handle();
	LedController::getInstance()->handle();
}
