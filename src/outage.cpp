#include "outage.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "secrets.h"

//

namespace
{
    const char *powerInterruptionUrl = "http://localhost:4000/api/power/interruption";
    constexpr unsigned long postIntervalMs = 5000;
    unsigned long lastPowerInterruptionSentAt = 0;

    //

    void postPowerInterruption(bool powered)
    {
        JsonDocument json;
        json["powered"] = powered;

        String body;
        serializeJson(json, body);

        HTTPClient http;
        http.begin(powerInterruptionUrl);
        http.addHeader("Content-Type", "application/json");

        int responseCode = http.POST(body);
        if (responseCode <= 0) Serial.printf("Power interruption POST failed: %s\n", http.errorToString(responseCode).c_str());

        http.end();
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
        if (WiFi.status() != WL_CONNECTED) return;

        bool powered = digitalRead(SSR_PWR_INTRPT_PIN) == HIGH;
        postPowerInterruption(powered);
        lastPowerInterruptionSentAt = now;
    }
}
