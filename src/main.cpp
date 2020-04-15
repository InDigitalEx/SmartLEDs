/*
	Main file of firmware
*/

#include <Arduino.h>
ADC_MODE(ADC_VCC)

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_INTERRUPT_RETRY_COUNT 0

#include <FastLED.h>
FASTLED_USING_NAMESPACE

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

OtaHandler otaHandler;
SerialManager serialManager;

ESP8266WebServer webServer(80);
CRGB leds[NUM_LEDS];

void setup() {
	// Init Serial port
	serialManager.begin(115200);

	// Init OTA
	otaHandler.begin(true);

	// Init fastled
	FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds, NUM_LEDS);
	FastLED.setDither(false);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(30);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, AMPERAGE);
	FastLED.show();

	// Init Wifi connection with manager
	WiFiManager wifiManager;
	wifiManager.autoConnect();
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	wifiManager.setDebugOutput(DEBUG);
	serialManager.printDebug();
}

void loop() {
	FastLED.delay(1000 / FRAMES_PER_SECOND);
	otaHandler.handle();
}
