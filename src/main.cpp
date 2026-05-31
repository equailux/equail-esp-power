#include <Arduino.h>
#include "./station.h"
#include "./level.h"
#include "./outage.h"

//

void setup()
{
    Serial.begin(115200);

    sta::setup();
    pvl::setupLevel();
    ptg::setupOutage();
}

void loop()
{
    pvl::loopLevel();
    ptg::loopOutage();
}
