#pragma once

#include <ESP8266WiFi.h>

class LedY
{
public:
    LedY(int pin);
    void SetOn(bool isOn);

private:
    int _pin;
};