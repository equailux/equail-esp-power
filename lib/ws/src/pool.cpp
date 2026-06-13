#include "pool.h"

//

namespace ws
{
    std::vector<EventHandler> onEventCallbacks;

    std::vector<void (*)()> onConnectedCallbacks;

    std::vector<void (*)()> onDisconnectedCallbacks;
}