/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <EEPROM.h>
#include <WiFiManager.h>

#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))

#include "serialmanager.h"
#include "otahandler.h"
#include "lightmanager.h"

OtaHandler otaHandler;
SerialManager serialManager;

ESP8266WebServer webServer(80);

void setup() {
	// Init Serial port
	serialManager.begin(115200);

	// Init OTA
	otaHandler.begin(true);

	// Init Wifi connection with manager
	WiFiManager wifiManager;
	wifiManager.autoConnect();
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	wifiManager.setDebugOutput(DEBUG);
	serialManager.printDebug();
	LightManager::getInstance()->begin();
}

void loop() {
	otaHandler.handle();
}
