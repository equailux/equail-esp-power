#pragma once
#include "type.h"
#include <vector>

//

namespace ws
{
    /** Holds the event handlers to be called later. */
    extern std::vector<EventHandler> onEventCallbacks;
    
    /** Holds the on connected handlers to be called later. */
    extern std::vector<void (*)()> onConnectedCallbacks;
    
    /** Holds the on disconnected handlers to be called later. */
    extern std::vector<void (*)()> onDisconnectedCallbacks;
}