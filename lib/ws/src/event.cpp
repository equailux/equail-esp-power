#include "event.h"
#include "pool.h"
#include "codec.h"

//

namespace ws
{
    void onWebSocketEvent(WStype_t type, uint8_t *payload, size_t length)
    {
        switch (type)
        {
        /** Invokes registered onDisconnected event handlers. */
        case WStype_DISCONNECTED:
        {
            for (void (*callback)() : onDisconnectedCallbacks)
                callback();
            break;
        }
        /** Invokes registered onConnected event handlers. */
        case WStype_CONNECTED:
        {
            for (void (*callback)() : onConnectedCallbacks)
                callback();
            break;
        }
        /** Encodes message to event and invokes matching handlers. */
        case WStype_TEXT:
        {
            // --- Raw String Data
            String text = String((char *)payload).substring(0, length);
            Serial.printf("WebSocket received message: %s.\n", text.c_str());

            // --- Event conversion
            JsonDocument doc;
            JsonArray arr = doc.to<JsonArray>();
            Event event = { String(""), arr, EventQuery::Create };

            if (encodeEvent(text, event))
            {
                Serial.printf("WebSocket received \"%s:%d\" event.\n", event.name.c_str(), event.query);

                for (const EventHandler &handler : onEventCallbacks)
                {
                    bool match = event.name.equals(handler.name);
                    match = match && event.query == handler.query;
                    
                    if (match && handler.callback)
                    {
                        handler.callback(event.data);
                        Serial.printf("WebSocket event matches \"%s:%d\" handler.\n", handler.name, handler.query);
                    }

                    yield();
                }
            }
            else Serial.printf("WebSocket received invalid event: %s.\n", text.c_str());
            break;
        }
        case WStype_PING:
        {
            Serial.printf("WebSocket received PING: %s.\n", !!payload ? (char *)payload : "");
        }
        case WStype_PONG:
        {
            Serial.printf("WebSocket received PONG: %s.\n", !!payload ? (char *)payload : "");
        }
        }
    }
}