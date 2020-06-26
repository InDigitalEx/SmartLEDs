#include "serialmanager.h"

void SerialManager::begin(const unsigned long baud = 115200) {
	Serial.begin(115200);
	Serial.setDebugOutput(DEBUG);
	delay(100); // For relability
}

void SerialManager::printDebug() {
	Serial.println("DEBUG INFO:\n");
	Serial.print("Free Heap: ");
	Serial.println(ESP.getFreeHeap());
	Serial.print("Boot Mode: ");
	Serial.println(ESP.getBootMode());
	Serial.print("Boot ver.: ");
	Serial.println(ESP.getBootVersion());
	Serial.print("Chip ID: ");
	Serial.println(ESP.getChipId());
	Serial.print("Core ver.: ");
	Serial.println(ESP.getCoreVersion());
	Serial.print("CPU freq: ");
	Serial.println(ESP.getCpuFreqMHz());
	Serial.print("Flash chip ID: ");
	Serial.println(ESP.getFlashChipId());
	Serial.print("Flash chip mode: ");
	Serial.println(ESP.getFlashChipMode());
	Serial.print("Flash chip real size: ");
	Serial.println(ESP.getFlashChipRealSize());
	Serial.print("Flash chip size: ");
	Serial.println(ESP.getFlashChipSize());
	Serial.print("Flash chip vendor ID: ");
	Serial.println(ESP.getFreeContStack());
	Serial.print("Free sketch space: ");
	Serial.println(ESP.getFreeSketchSpace());
	Serial.print("Full version: ");
	Serial.println(ESP.getFullVersion());
	Serial.print("Heap fragmentation: ");
	Serial.println(ESP.getHeapFragmentation());
	Serial.print("Max free block size: ");
	Serial.println(ESP.getMaxFreeBlockSize());
	Serial.print("Reset info: ");
	Serial.println(ESP.getResetInfo());
	Serial.print("Reset reason: ");
	Serial.println(ESP.getResetReason());
	Serial.print("Sketch size: ");
	Serial.println(ESP.getSketchSize());
	Serial.print("ESP Voltage: ");
	Serial.println(ESP.getVcc() / 1024.0);
	Serial.println();
}
