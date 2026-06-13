#pragma once
#include <Arduino.h>
#include <WebSocketsClient.h>

//

namespace ws
{
    /** The main callback event for the WebSocket client. */
    void onWebSocketEvent(WStype_t type, uint8_t *payload, size_t length);
}