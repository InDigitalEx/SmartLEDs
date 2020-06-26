/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

#include <WiFiManager.h>
#include "serialmanager.h"
#include "otahandler.h"
#include "lightmanager.h"

OtaHandler ota;
SerialManager serial;

void setup() {
	// Init Serial
	serial.begin(115200);

	// Init OTA
	ota.begin(true);

	// Init SFX
	LightManager::getInstance()->begin();

	// Init Wifi connection manager
	WiFiManager wifiManager;
	wifiManager.autoConnect();
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	wifiManager.setDebugOutput(DEBUG);

	serial.printDebug();
}

void loop() {
	ota.handle();
	LightManager::getInstance()->handle();
}
