#pragma once

#include <ESP8266WiFi.h>

class WifiServerY
{
public:
    WifiServerY(std::string wifiName, std::string wifiPassword,
                std::string ip, std::string gate, std::string sub,
                int port);

    void ProcessClient();
    void SendString(String str);

private:
    WiFiServer *_server;
    WiFiClient _client;

    bool _isWifiConnected;
    bool _isClientOK;
};
