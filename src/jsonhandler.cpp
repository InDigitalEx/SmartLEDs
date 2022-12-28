#include "jsonhandler.h"
#include <ArduinoJson.h>
#include "ledcontroller.h"
#include "palette.h"

static LedController* controller = LedController::getInstance();
static Manager<Effect>* effects = controller->getEffects();
static Manager<Palette>* palettes = controller->getPalettes();

void JsonHandler::init() {

}

void JsonHandler::generateJson(String &destination) {
    /*
        {
            "effects": [
                [
                    "name",     // Name
                    255,        // Brightness
                    7,          // Modes
                    3,          // Mode
                    [
                        [
                            0,      // Index in array
                            "Name"  // Name of setting
                            255,    // Value
                            0,      // Min value
                            255     // Max value
                        ]
                    ]
                ]
            ],
            "palettes": [
                "name",         // Name of palette
                "name"
            ]
        }
    */
    DynamicJsonDocument doc(2048); // TODO: dynamic value calculation

    // Fill effects array
    JsonArray effectsJson = doc.createNestedArray("effects");

    auto effectsVector = effects->getVectorOfData();
    size_t effectsSize = effectsVector->size();

    for(size_t i = 0; i < effectsSize; i++) {
        JsonArray effect = effectsJson.createNestedArray();
        Effect *e = effectsVector->at(i);

        effect.add(e->name());
        effect.add(e->brightness()->get());
        effect.add(e->availableModes()->get());
        effect.add(e->mode()->get());

        // Fill settings array
        auto settingsVector = e->settings();
        size_t settingsSize = settingsVector->size();
        JsonArray settings = effect.createNestedArray();

        for(size_t j = 0; j < settingsSize; j++) {
            JsonArray setting = settings.createNestedArray();
            Setting *s = settingsVector->at(j);

            setting.add(s->getName());
            setting.add(s->get());
            setting.add(s->getMinValue());
            setting.add(s->getMaxValue());
        }
    }

    // Fill palettes array
    JsonArray palettesJson = doc.createNestedArray("palettes");

    auto palettesVector = palettes->getVectorOfData();
    size_t palettesSize = palettesVector->size();
    
    for(size_t i = 0; i < palettesSize; i++) {
        palettesJson.add(palettesVector->at(i)->getName());
    }

    // Convert json document to string
    serializeJson(doc, destination);
}

void JsonHandler::handleIncomingText(const char* text) {
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(3)+32);

    DeserializationError error = deserializeJson(doc, text);
    if(error != DeserializationError::Ok) {
        #ifdef DEBUG
        Serial.printf("Deserialization Error: %s", error.c_str());
        #endif
        return;
    }

    if(doc.containsKey("effect")) {
        effects->setCurrent(doc["effect"]);
        #ifdef DEBUG
        Serial.printf("Set Current Effect to %d\n", doc["effect"].as<int>());
        #endif
    }
    else if(doc.containsKey("palette")) {
        palettes->setCurrent(doc["palette"]);
        #ifdef DEBUG
        Serial.printf("Set Current Palette to %d\n", doc["palette"].as<int>());
        #endif
    }
    else if(doc.containsKey("mode")) {
        effects->getCurrent()->mode()->set(doc["mode"]);
        #ifdef DEBUG
        Serial.printf("Set Current Mode to %d\n", doc["mode"].as<int>());
        #endif
    }
    else if(doc.containsKey("brightness")) {
        effects->getCurrent()->brightness()->set(doc["brightness"]);
        #ifdef DEBUG
        Serial.printf("Set Current Brightness to %d\n", doc["brightness"].as<int>());
        #endif
    }
    else if(doc.containsKey("power")) {
        controller->setPower(doc["power"].as<bool>());
        #ifdef DEBUG
        Serial.printf("Set power to %d\n", doc["power"].as<bool>());
        #endif
    }
    else if(doc.containsKey("setting")) {
        JsonObject setting = doc["setting"];
        SettingValue id = setting["id"];
        SettingValue value = setting["value"];
        effects->getCurrent()->settings()->at(id)->set(value);
        #ifdef DEBUG
        Serial.printf("Set settings[%d] to %d\n", id, value);
        #endif
    }
}
