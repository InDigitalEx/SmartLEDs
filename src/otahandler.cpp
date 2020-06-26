#include "otahandler.h"

void OtaHandler::begin(bool rebootOnSuccess = true){
	ArduinoOTA.onStart([]() {
		Serial.println("[OTA] Start");
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("[OTA] End");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		switch (error) {
		case OTA_AUTH_ERROR: {
			Serial.println("[OTA] Auth Failed");
			break;
		}
		case OTA_BEGIN_ERROR: {
			Serial.println("[OTA] Begin Failed");
			break;
		}
		case OTA_CONNECT_ERROR: {
			Serial.println("[OTA] Connect Failed");
			break;
		}
		case OTA_END_ERROR: {
			Serial.println("[OTA] End Failed");
			break;
		}
		case OTA_RECEIVE_ERROR: {
			Serial.println("[OTA] Receive Failed");
			break;
		}
		default: {
			Serial.printf("[OTA] Error[%u]", error);
		}
		}
	});
	ArduinoOTA.setRebootOnSuccess(rebootOnSuccess);
	ArduinoOTA.begin();
}

void OtaHandler::handle() {
	ArduinoOTA.handle();
}
