#pragma once
#include "type.h"
#include "registry.h"

//

/** Encapsulates all of project's WebSocket requirements. */
namespace ws
{
    /** Starts persistent connection to WebSocket. */
    void init(const char *host, uint16_t port, const char *url, const char *key = nullptr);

    /** Emits an event into the WebSocket. */
    void emit(Event event);
    
    /** Emits an event into the WebSocket. */
    void emit(String name, JsonArray &data, EventQuery query);
    
    /** Emits an event into the WebSocket. */
    void emit(String name, JsonObject &data, EventQuery query);

    /** Required to be called in the main loop. */
    void loop();

    /** Disconnects WebSocket. */
    void close();
}