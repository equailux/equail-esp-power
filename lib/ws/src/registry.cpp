#include "registry.h"
#include "pool.h"

//

namespace ws
{
    void onEvent(EventHandler handler)
    {
        onEventCallbacks.push_back(handler);
    }

    void onEvent(const char *event, EventQuery query, EventCallback callback)
    {
        onEventCallbacks.push_back({event, query, callback});
    }

    void onConnected(void (*callback)())
    {
        onConnectedCallbacks.push_back(callback);
    }

    void onDisconnected(void (*callback)())
    {
        onDisconnectedCallbacks.push_back(callback);
    }
}