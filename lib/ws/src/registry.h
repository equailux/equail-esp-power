#pragma once
#include "type.h"

//

namespace ws
{
    /** Adds a handler for a specific event-query. */
    void onEvent(EventHandler handler);
    
    /** Adds a handler for a specific event-query. */
    void onEvent(const char *event, EventQuery query, EventCallback callback);

    /** Adds a callback invoked once WebSocket gets connected. */
    void onConnected(void(*callback)());
    
    /** Adds a callback invoked once WebSocket gets disconnected. */
    void onDisconnected(void(*callback)());
}