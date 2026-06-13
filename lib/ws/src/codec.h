#pragma once
#include "type.h"

//

namespace ws
{
    /** Converts a string into an event. */
    bool encodeEvent(String &src, Event &dest);

    /** Converts an event into a string. */
    bool decodeEvent(Event &src, String &dest);

    /** Converts a string into an event query. */
    EventQuery encodeEventQuery(String query);

    /** Converts an event query into a string. */
    String decodeEventQuery(EventQuery query);
}