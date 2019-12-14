#include "US100Y.h"

US100Y::US100Y(int echoPin, int trigPin)
{
    _echoPin=echoPin;
    _trigPin=trigPin;

    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

void US100Y::SendPacket(long distance)
{
    unsigned int dist1 = distance;
    struct SerialMsg msg;
    msg.header = 0x6666;
    msg.len = sizeof(SerialMsg) - 2;
    msg.distance1 = dist1;
    msg.distance2 = 0;
    msg.distance3 = 0;
    msg.tail = 0x8888;

    unsigned char sendCs[50];
    memcpy(sendCs, &msg, sizeof(SerialMsg));
    Serial.write(sendCs, sizeof(SerialMsg) - 2);
}

//测距//
long US100Y::CalcDistance()
{
    long duration = 0;
    long cm = 0;
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    duration = pulseIn(_echoPin, HIGH);
    cm = duration / 29 / 2;

    return cm;
}