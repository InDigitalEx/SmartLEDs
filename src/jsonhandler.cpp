#include "jsonhandler.h"
#include <ArduinoJson.h>
#include "ledcontroller.h"
#include "palette.h"

static LedController* controller = LedController::getInstance();
static Manager<Effect>* effects = controller->getEffects();
static Manager<Palette>* palettes = controller->getPalettes();

void JsonHandler::init() {

    // Find max length of json document
    size_t effectsCount = effects->getSize();
    size_t palettesCount = palettes->getSize();

    maxJsonListLength_ = 
        JSON_ARRAY_SIZE(effectsCount)
        + JSON_ARRAY_SIZE(palettesCount)
        + palettesCount * JSON_OBJECT_SIZE(PALETTE_OBJECTS)
        + effectsCount * JSON_OBJECT_SIZE(EFFECT_OBJECTS)
        + JSON_OBJECT_SIZE(2) + ((effectsCount + palettesCount) * 24);
}

void JsonHandler::generateJsonList(String &destination) {
    DynamicJsonDocument doc(maxJsonListLength_);

    JsonArray effectsJson = doc.createNestedArray("Effects");
    JsonArray palettesJson = doc.createNestedArray("Palettes");

    // Create effects array
    auto effectsVector = effects->getVectorOfData();
    for(auto e : *effectsVector) {
        JsonObject effect = effectsJson.createNestedObject();

        effect["Name"] = e->getName();
        effect["Speed"] = e->getSpeed();
        effect["Scale"] = e->getScale();
        effect["Params"] = e->getParams();
        effect["Brightness"] = e->getBrightness();
    }
    
    // Create palettes array
    auto palettesVector = palettes->getVectorOfData();
    for(auto p : *palettesVector) {
        JsonObject palette = palettesJson.createNestedObject();
        palette["Name"] = p->getName();
    }

    // Convert json doc to string
    serializeJson(doc, destination);
}

void JsonHandler::handleIncomingText(uint8_t* text) {
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(7) + 53);

    DeserializationError error = deserializeJson(doc, text);
    if(error != DeserializationError::Ok) {
        #ifdef DEBUG
        Serial.printf("Deserialization Error: %s", error.c_str());
        #endif
        return;
    }

    if(doc.containsKey("EffectId")) {
        effects->setCurrent(doc["EffectId"]);
        #ifdef DEBUG
        Serial.printf("Set Current Effect to %d", doc["EffectId"].as<int>());
        #endif
    }
    if(doc.containsKey("PaletteId")) {
        palettes->setCurrent(doc["PaletteId"]);
        #ifdef DEBUG
        Serial.printf("Set Current Palette to %d", doc["PaletteId"].as<int>());
        #endif
    }
    if(doc.containsKey("Speed")) {
        effects->getCurrent()->setSpeed(doc["Speed"]);
        #ifdef DEBUG
        Serial.printf("Set Current Speed to %d", doc["Speed"].as<int>());
        #endif
    }
    if(doc.containsKey("Scale")) {
        effects->getCurrent()->setScale(doc["Scale"]);
        #ifdef DEBUG
        Serial.printf("Set Current Scale to %d", doc["Scale"].as<int>());
        #endif
    }
    if(doc.containsKey("Brightness")) {
        effects->getCurrent()->setBrightness(doc["Brightness"]);
        #ifdef DEBUG
        Serial.printf("Set Current Brightness to %d", doc["Brightness"].as<int>());
        #endif
    }
    if(doc.containsKey("Mode")) {
        effects->getCurrent()->setMode(doc["Mode"]);
        #ifdef DEBUG
        Serial.printf("Set Current Mode to %d", doc["Mode"].as<int>());
        #endif
    }
    if(doc.containsKey("Power")) {
        controller->setPower(doc["Power"].as<bool>());
        #ifdef DEBUG
        Serial.printf("Set power to %d", doc["Power"].as<bool>());
        #endif
    }
}