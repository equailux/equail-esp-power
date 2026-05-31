#include "level.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "secrets.h"

//

namespace 
{
    const char *powerUrl = "http://localhost:4000/api/power";
    constexpr unsigned long postIntervalMs = 5000;
    constexpr float analogMaxReading = 4095.0f;
    unsigned long lastPowerLevelSentAt = 0;

    //

    void postPowerLevel(float level)
    {
        JsonDocument json;
        json["level"] = level;

        String body;
        serializeJson(json, body);

        HTTPClient http;
        http.begin(powerUrl);
        http.addHeader("Content-Type", "application/json");

        int responseCode = http.POST(body);
        if (responseCode <= 0) Serial.printf("Power level POST failed: %s\n", http.errorToString(responseCode).c_str());

        http.end();
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
        if (WiFi.status() != WL_CONNECTED) return;

        int reading = analogRead(SSR_PWR_LVL_PIN);
        float level = (reading / analogMaxReading) * 100.0f;
        
        postPowerLevel(level);
        lastPowerLevelSentAt = now;
    }
}
