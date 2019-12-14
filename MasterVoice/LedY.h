#pragma once

#include <ESP8266WiFi.h>

class LedY
{
public:
    LedY(int ledPin);
    void SetOn(bool isOn);

private:
    int _ledPin;
};