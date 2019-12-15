#include "SR602Y.h"

SR602Y::SR602Y(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

bool SR602Y::HasSignal()
{
    int state = digitalRead(_pin);
    if (state == HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}