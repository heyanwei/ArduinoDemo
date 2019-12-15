#include "LedY.h"

LedY::LedY(int pin)
{
    _pin=pin;

    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void LedY::SetOn(bool isOn)
{
    if(isOn)
    {
        digitalWrite(_pin, HIGH);
    }
    else
    {
        digitalWrite(_pin, LOW);       
    }
    
}