/*
 * Name: Wilson
 * Description: 
 * 1. 用于初步的测试
 * 2. 建立服务端，以发送和接收数据
 * 3. 如果连接正常，把灯点亮，如果连接异常，把灯熄灭
 */

#include "US100Y.h"
#include "WifiServerY.h"

US100Y *_us100;
WifiServerY *_server;

void setup()
{
  //波特率115200，数据位8，偶校验，停止位2
  //Serial.begin(115200, SERIAL_8E2);
  Serial.begin(9600);

  // _server = new WifiServerY("YFRobot","yfjqr2015","172.16.1.132",
  //     "172.16.1.1", "255.255.255.0", 80);
  _server = new WifiServerY("YFRobot","yfjqr2015","",
      "", "", 80);
  _us100 = new US100Y(12,13);
}

void loop()
{
  if ((!_server)||(!_us100))
  {
    return;   
  }
  _server->ProcessClient();

  long dist = _us100->CalcDistance();
  String data="Distance: ";
  data+=dist;

  Serial.println(data);
  _server->SendString(data);

  delay(300);
}
