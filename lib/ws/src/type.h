#pragma once
#include <ArduinoJson.h>

//

namespace ws
{
    /**
     * Determines what the event wants.
     */
    enum class EventQuery
    {
        Create,
        Retrieve,
        Update,
        Delete,
    };

    /**
     * Invoked once matched.
     */
    using EventCallback = void (*)(JsonArray);

    /**
     * Represents event name, type, and callback.
     */
    struct EventHandler
    {
        const char *name;
        EventQuery query;
        EventCallback callback;
    };

    /**
     * Represents event name, type, and data.
     */
    struct Event
    {
        String name;
        JsonArray data;
        EventQuery query;
    };
}