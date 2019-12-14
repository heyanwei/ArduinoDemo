#include "WifiServerY.h"

WifiServerY::WifiServerY(std::string wifiName, std::string wifiPassword,
                         std::string ip, std::string gate, std::string sub,
                         int port)
{
    _isWifiConnected = false;
    _isClientOK = false;

    _server = new WiFiServer(port);

    IPAddress ipAddr;
    IPAddress gateWay;
    IPAddress subNet;
    if (ipAddr.fromString(ip.c_str()) && gateWay.fromString(
        gate.c_str()) && subNet.fromString(sub.c_str()))
    {
        WiFi.config(ipAddr, gateWay, subNet);       
    }
    else
    {
        Serial.println("Cant use static IP Address ...");
    }
    

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiName.c_str(), wifiPassword.c_str());
}

void WifiServerY::ProcessClient()
{
    if (!_isWifiConnected)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("WIFI Connect finish ...");

            _server->begin();
            Serial.print("Server Started, ip address is ");
            Serial.println(WiFi.localIP());

            _isWifiConnected = true;
        }
        else
        {
            return;
        }
    }
    if (!_isClientOK)
    {
        _client = _server->available();
        if (_client)
        {
            _isClientOK = true;
            Serial.print("Client connect...");
            Serial.println(_client.remoteIP());
        }
        else
        {
            return;
        }
    }
    if (!_client)
    {
        _isClientOK = false;
        Serial.println("_client is null");
        return;
    }

    String data = "";
    while (_client.available() > 0)
    {
        data += char(_client.read());
    }
    if (data.length() > 0)
    {
        Serial.println(data);
    }
}

void WifiServerY::SendString(String str)
{
    if (!_client)
    {
        return;
    }
    _client.println(str);
    _client.flush();
}