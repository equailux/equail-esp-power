#include "level.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "ws.h"
#include "secrets.h"

//

namespace 
{
    constexpr unsigned long postIntervalMs = 5000;
    constexpr float analogMaxReading = 3400.0f;
    unsigned long lastPowerLevelSentAt = 0;

    //

    void emitPowerLevel(float level)
    {
        JsonDocument doc;
        JsonObject data = doc.to<JsonObject>();
        data["level"] = level;
        data["unit"] = "%";

        ws::emit("Power", data, ws::EventQuery::Create);
    }
}

namespace pvl
{
    void setupLevel()
    {
        pinMode(SSR_PWR_LVL_PIN, INPUT);
        lastPowerLevelSentAt = millis() - postIntervalMs;
    }

    void loopLevel()
    {
        unsigned long now = millis();
        if (now - lastPowerLevelSentAt < postIntervalMs) return;

        int reading = analogRead(SSR_PWR_LVL_PIN);
        float level = (reading / analogMaxReading) * 100.0f;
        
        emitPowerLevel(level);
        lastPowerLevelSentAt = now;
    }
}
