#include <Arduino.h>
#include <HardwareSerial.h>
#include "serialmanager.h"

void SerialManager::init(const unsigned long baud = 115200) {
	Serial.begin(115200);
	#ifdef DEBUG
	Serial.setDebugOutput(true);
	#endif
	delay(100); // For relability
}
void SerialManager::printDebugInfo() {
	Serial.println(F("DEBUG INFO:\n"));
	Serial.print(F("Free Heap: "));
	Serial.println(ESP.getFreeHeap());
	Serial.print(F("Boot Mode: "));
	Serial.println(ESP.getBootMode());
	Serial.print(F("Boot ver.: "));
	Serial.println(ESP.getBootVersion());
	Serial.print(F("Chip ID: "));
	Serial.println(ESP.getChipId());
	Serial.print(F("Core ver.: "));
	Serial.println(ESP.getCoreVersion());
	Serial.print(F("CPU freq: "));
	Serial.println(ESP.getCpuFreqMHz());
	Serial.print(F("Flash chip ID: "));
	Serial.println(ESP.getFlashChipId());
	Serial.print(F("Flash chip mode: "));
	Serial.println(ESP.getFlashChipMode());
	Serial.print(F("Flash chip real size: "));
	Serial.println(ESP.getFlashChipRealSize());
	Serial.print(F("Flash chip size: "));
	Serial.println(ESP.getFlashChipSize());
	Serial.print(F("Flash chip vendor ID: "));
	Serial.println(ESP.getFreeContStack());
	Serial.print(F("Free sketch space: "));
	Serial.println(ESP.getFreeSketchSpace());
	Serial.print(F("Full version: "));
	Serial.println(ESP.getFullVersion());
	Serial.print(F("Heap fragmentation: "));
	Serial.println(ESP.getHeapFragmentation());
	Serial.print(F("Max free block size: "));
	Serial.println(ESP.getMaxFreeBlockSize());
	Serial.print(F("Reset info: "));
	Serial.println(ESP.getResetInfo());
	Serial.print(F("Reset reason: "));
	Serial.println(ESP.getResetReason());
	Serial.print(F("Sketch size: "));
	Serial.println(ESP.getSketchSize());
	Serial.print(F("ESP Voltage: "));
	Serial.println(ESP.getVcc() / 1024.0);
	Serial.println();
}
