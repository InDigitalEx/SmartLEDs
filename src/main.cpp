/*
	Main file of firmware
*/

#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "serialmanager.h"
//#include "otaupdater.h"
#include "ledcontroller.h"
#include "web.h"

//static OtaUpdater otaUpdater;
static SerialManager serial;
static LedController *ledController = LedController::getInstance();
static Web *web = Web::getInstance();

// Effect Processing Thread
TaskHandle_t ledTask;
void ledTaskHandle(void* pvParameters);

void setup() {
	// Initializing a Serial Buffer
	serial.init(115200);

	// Initializing a new thread for processing effects
	xTaskCreatePinnedToCore(ledTaskHandle, "LedTask", 10000, NULL, 1, &ledTask, 0);
	
	// Initializing a Wi-Fi connection
	WiFi.begin("TP-Link_0A9A", "yGMau42i");

	while(WiFi.status() != WL_CONNECTED) {
		Serial.print("*");
		delay(100);
	}
	Serial.println();

	// Init web module
	web->init();

	// Init OTA
	//otaUpdater.init(true);

	#ifdef DEBUG
	//serial.printDebugInfo();
	serial.printMemInfo();
	#endif
}

void loop() {
	web->handle();
	//otaUpdater.handle();
	yield();
}

void ledTaskHandle(void* pvParameters) {
	ledController->init();

	while (true) {
		randomSeed(micros());
		random16_add_entropy(random(0xFFFF));

		ledController->handle();

		#ifdef DEBUG
		EVERY_N_SECONDS(10) {
			Serial.println(FastLED.getFPS());
		}
		#endif
	}
}
