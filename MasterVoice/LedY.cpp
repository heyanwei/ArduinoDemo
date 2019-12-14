#include "LedY.h"

LedY::LedY(int ledPin)
{
    _ledPin=ledPin;

    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, LOW);
}

void LedY::SetOn(bool isOn)
{
    if(isOn)
    {
        digitalWrite(_ledPin, HIGH);
    }
    else
    {
        digitalWrite(_ledPin, LOW);       
    }
    
}