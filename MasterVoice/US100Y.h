#pragma once

#include <ESP8266WiFi.h>

struct SerialMsg
{
    unsigned short header;
    unsigned short len;
    unsigned int distance1;
    unsigned int distance2;
    unsigned int distance3;
    unsigned short tail;
};

class US100Y
{
public:
    US100Y(int echoPin, int trigPin);

    long CalcDistance();
    void SendPacket(long distance);

private:
    int _echoPin;
    int _trigPin;
};
