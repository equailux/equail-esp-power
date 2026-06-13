#include "main.h"
#include "event.h"
#include "codec.h"
#include "queue.h"
#include "instance.h"

//

namespace ws
{
    void init(const char *host, uint16_t port, const char *url, const char *key)
    {
        /** Bind events and configs. */
        client.onEvent(onWebSocketEvent);
        client.enableHeartbeat(15000, 3000, 2);
        client.setReconnectInterval(5000);
        if (key != nullptr)
        {
            client.setExtraHeaders((String("x-api-key: ") + key).c_str());
        }

        if (port == 443)
        {
            client.beginSSL(host, port, url);
        }
        else if (!strcmp(host, "gateway"))
        {
            /** Uses the WiFi's gateway IP as host. */
            String ipStr = WiFi.gatewayIP().toString();
            client.begin(ipStr.c_str(), port, url);
        }
        else
        {
            client.begin(host, port, url);
        }
    }

    void emit(Event event)
    {
        String text;
        if (decodeEvent(event, text))
            eventQueue.push_back(text);
        else 
            Serial.printf("WebSocket emit() failed to decode event, it will not be sent.\n");
    }

    void emit(String name, JsonArray &data, EventQuery query)
    {
        Event event = {name, data, query};
        emit(event);
    }

    void emit(String name, JsonObject &data, EventQuery query)
    {
        JsonDocument doc;
        JsonArray arr = doc.to<JsonArray>();
        arr.add<JsonObject>().set(data);

        Event event = {name, arr, query};
        emit(event);
    }

    void loop()
    {
        client.loop();

        if (!eventQueue.empty())
        {
            String oldest = eventQueue.front();
            if (client.sendTXT(oldest))
            {
                Serial.printf("WebSocket sent %s.\n", oldest.c_str());
                eventQueue.erase(eventQueue.begin());
            }
        }
    }

    void close()
    {
        client.disconnect();
    }
}