#include <Arduino.h>
#include "./station.h"
#include "./websocket.h"
#include "./level.h"
#include "./outage.h"

//

void setup()
{
    Serial.begin(115200);
    sta::setup();
    wsc::setup();
    pvl::setupLevel();
    ptg::setupOutage();
}

void loop()
{
    if (!wsc::loop()) return;
    pvl::loopLevel();
    ptg::loopOutage();
}
