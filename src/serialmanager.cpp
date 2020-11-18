#include "serialmanager.h"
#include <Arduino.h>
#include <HardwareSerial.h>


void SerialManager::init(const unsigned long baud = 115200) {
	Serial.begin(115200);
	#ifdef DEBUG
	Serial.setDebugOutput(true);
	#endif
	delay(100); // For relability
}

void SerialManager::printDebugInfo() {
	Serial.printf("DEBUG INFO:\nBoot Mode: %d\nBoot version: %d\nFree Heap: %d\nCPU freq: %d\n\
		Flash chip speed: %d\nFlash chip size: %d\nFree sketch space: %d\nSketch size: %d\nFree heap: %d\n\
		Heap fragmentation: %d\nMax free block size: %d\nReset info: %s\nReset reason: %s\nVoltage: %f\n",
		ESP.getBootMode(), ESP.getBootVersion(), ESP.getFreeHeap(), ESP.getCpuFreqMHz(),
		ESP.getFlashChipSpeed(), ESP.getFlashChipSize(), ESP.getFreeSketchSpace(),
		ESP.getSketchSize(), ESP.getFreeHeap(), ESP.getHeapFragmentation(), ESP.getMaxFreeBlockSize(),
		ESP.getResetInfo().c_str(), ESP.getResetReason().c_str(), (ESP.getVcc() / 1024.0));
}
