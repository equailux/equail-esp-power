#include "websocket.h"
#include <WiFi.h>
#include "ws.h"
#include "secrets.h"

//

namespace wsc
{
    bool ready = false;

    //

    void onWiFiConnected(WiFiEvent_t event);

    //

    void setup()
    {
        WiFi.onEvent(onWiFiConnected);
        Serial.printf("WebSocket connection initialized.\n");
        ws::onConnected([]() -> void { ready = true; });
        ws::onConnected([]() -> void { Serial.printf("WebSocket connected successfully.\n"); });
        ws::onDisconnected([]() -> void { ready = false; });
        ws::onDisconnected([]() -> void { Serial.printf("WebSocket disconnected unfortunately.\n"); });
    }

    bool loop()
    {
        ws::loop();
        return ready;
    }

    void onWiFiConnected(WiFiEvent_t event)
    {
        if (event != WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP) return;
        Serial.printf("WebSocket now connecting.\n");
        ws::init(WS_HOST, WS_PORT, WS_PATH, WS_KEY);
    }
}
