#include "serialmanager.h"
#include <Arduino.h>
#include <HardwareSerial.h>


void SerialManager::init(const unsigned long baud = 115200) {
	Serial.begin(115200);
	#ifdef DEBUG
	Serial.setDebugOutput(true);
	#endif
	while(!Serial)
		continue; // For relability
}

void SerialManager::printDebugInfo() {
	Serial.printf("DEBUG INFO:\nBoot Mode: %d\nCPU freq: %d\nFlash chip speed: %d\nFlash chip size: %d\n\
	Free sketch space: %d\nSketch size: %d\nFree heap: %d\nHeap fragmentation: %d\nMax free block size: %d\n\
	Free stack: %d\nReset reason: %s\nVoltage: %f\n",
		ESP.getBootMode(), ESP.getCpuFreqMHz(),
		ESP.getFlashChipSpeed(), ESP.getFlashChipSize(), ESP.getFreeSketchSpace(),
		ESP.getSketchSize(), ESP.getFreeHeap(), ESP.getHeapFragmentation(), ESP.getMaxFreeBlockSize(),
		ESP.getFreeContStack(), ESP.getResetReason().c_str(), (ESP.getVcc() / 1024.0));
}

void SerialManager::printMemInfo() {
	Serial.printf("Stack: %i, Heap: %i\n", ESP.getFreeContStack(), ESP.getFreeHeap());
}
