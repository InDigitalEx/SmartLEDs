#include "jsonhandler.h"
#include <ArduinoJson.h>
#include "ledcontroller.h"
#include "palette.h"

static LedController* controller = LedController::getInstance();

void JsonHandler::init() {

    // Find max length of json document
    size_t effectsCount = controller->getVectorOfEffects()->size();
    size_t palettesCount = controller->getVectorOfPalettes()->size();

    maxJsonListLength_ = 
        JSON_ARRAY_SIZE(effectsCount)
        + JSON_ARRAY_SIZE(palettesCount)
        + palettesCount * JSON_OBJECT_SIZE(PALETTE_OBJECTS)
        + effectsCount * JSON_OBJECT_SIZE(EFFECT_OBJECTS)
        + JSON_OBJECT_SIZE(2) + ((effectsCount + palettesCount) * 24);
}

void JsonHandler::generateJsonList(String &destination) {
    DynamicJsonDocument doc(maxJsonListLength_);

    JsonArray effects = doc.createNestedArray("Effects");
    JsonArray palettes = doc.createNestedArray("Palettes");

    // Create effects array
    std::vector<Effect *> *effectsPtr = controller->getVectorOfEffects();
    for(size_t i = 0; i < effectsPtr->size(); i++) {
        JsonObject effect = effects.createNestedObject();
        Effect* el = effectsPtr->at(i);

        effect["Name"] = el->getName();
        effect["Speed"] = el->getSpeed();
        effect["Scale"] = el->getScale();
        effect["Flags"] = el->getFlags();
        effect["Brightness"] = el->getBrightness();
    }
    
    // Create palettes array
    std::vector<Palette *> *palettesPtr = controller->getVectorOfPalettes();
    for(size_t i = 0; i < palettesPtr->size(); i++) {
        JsonObject palette = palettes.createNestedObject();
        palette["Name"] = palettesPtr->at(i)->name;
    }

    // Convert json doc to string
    serializeJson(doc, destination);
}