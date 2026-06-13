#include "outage.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "ws.h"
#include "secrets.h"

//

namespace
{
    constexpr unsigned long postIntervalMs = 5000;
    unsigned long lastPowerInterruptionSentAt = 0;

    //

    void emitPowerInterruption(bool powered)
    {
        JsonDocument doc;
        JsonObject data = doc.to<JsonObject>();
        data["powered"] = powered;

        ws::emit("PowerInterruption", data, ws::EventQuery::Create);
    }
}

namespace ptg
{
    void setupOutage()
    {
        pinMode(SSR_PWR_INTRPT_PIN, INPUT);
        lastPowerInterruptionSentAt = millis() - postIntervalMs;
    }

    void loopOutage()
    {
        unsigned long now = millis();
        if (now - lastPowerInterruptionSentAt < postIntervalMs) return;

        bool powered = digitalRead(SSR_PWR_INTRPT_PIN) == HIGH;
        emitPowerInterruption(powered);
        lastPowerInterruptionSentAt = now;
    }
}   
