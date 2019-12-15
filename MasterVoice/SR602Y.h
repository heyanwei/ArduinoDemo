#pragma once

#include <ESP8266WiFi.h>

class SR602Y
{
public:
    SR602Y(int pin);

    bool HasSignal();

private:
    int _pin;
};