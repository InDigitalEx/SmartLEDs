#include <Arduino.h>
ADC_MODE(ADC_VCC) // Устанавливаем АЦП в режим измерения напряжения на VCC

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>

extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <EEPROM.h>
#include <WiFiManager.h>

// Sketch settings
#define DATA_PIN            D2
#define LED_TYPE            WS2812B
#define LED_ORDER           GRB
#define NUM_LEDS            120

#define MILLI_AMPS          3000    // Максимальный ток блока питания в мА (3А == 3000мА)
#define FRAMES_PER_SECOND   120     // Если лагает анимация - уменьшайте это значение

/////////////////////////////////////////
ESP8266WebServer webServer(80);
ESP8266HTTPUpdateServer httpUpdateServer;

CRGB leds[NUM_LEDS];
/////////////////////////////////////////

void PrintDebugInfo() {
    #ifdef DEBUG
    Serial.println("");
    Serial.print("Free Heap: ");            Serial.println(ESP.getFreeHeap());
    Serial.print("Boot Mode: ");            Serial.println(ESP.getBootMode());
    Serial.print("Boot ver.: ");            Serial.println(ESP.getBootVersion());
    Serial.print("Chip ID: ");              Serial.println(ESP.getChipId());
    Serial.print("Core ver.: ");            Serial.println(ESP.getCoreVersion());
    Serial.print("CPU freq: ");             Serial.println(ESP.getCpuFreqMHz());
    Serial.print("Flash chip ID: ");        Serial.println(ESP.getFlashChipId());
    Serial.print("Flash chip mode: ");      Serial.println(ESP.getFlashChipMode());
    Serial.print("Flash chip real size: "); Serial.println(ESP.getFlashChipRealSize());
    Serial.print("Flash chip size: ");      Serial.println(ESP.getFlashChipSize());
    Serial.print("Flash size by chip ID: ");Serial.println(ESP.getFlashChipSizeByChipId());
    Serial.print("Flash chip speed: ");     Serial.println(ESP.getFlashChipSpeed());
    Serial.print("Flash chip vendor ID: "); Serial.println(ESP.getFlashChipVendorId());
    Serial.print("Free cont. stack: ");     Serial.println(ESP.getFreeContStack());
    Serial.print("Free sketch space: ");    Serial.println(ESP.getFreeSketchSpace());
    Serial.print("Full version: ");         Serial.println(ESP.getFullVersion());
    Serial.print("Heap fragmentation: ");   Serial.println(ESP.getHeapFragmentation());
    Serial.print("Max free block size: ");  Serial.println(ESP.getMaxFreeBlockSize());
    Serial.print("Reset info: ");           Serial.println(ESP.getResetInfo());
    Serial.print("Reset reason: ");         Serial.println(ESP.getResetReason());
    Serial.print("SDK version: ");          Serial.println(ESP.getSdkVersion());
    Serial.print("Sketch size: ");          Serial.println(ESP.getSketchSize());
    Serial.print("ESP Voltage: ");          Serial.println(ESP.getVcc() / 1024.0);
    Serial.println();
    #endif // DEBUG
}

void setup() {
    WiFi.setSleepMode(WIFI_NONE_SLEEP);

    // Инициализация serial
    Serial.begin(115200);
    delay(100);
    Serial.setDebugOutput(DEBUG);

    // Инициализация библиотеки для адресной ленты
    FastLED.addLeds<LED_TYPE, DATA_PIN, LED_ORDER>(leds, NUM_LEDS);
    FastLED.setDither(false);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(30);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    // Инициализируем WiFi подключение через менеджер
    WiFiManager wifiManager;
    wifiManager.autoConnect();
    wifiManager.setDebugOutput(DEBUG);

    // Вывод информации о железе
    PrintDebugInfo();
}

void loop() {
}
