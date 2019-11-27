/*
 * Name: Wilson
 * Description: 
 * 1. 用于初步的测试
 * 2. 建立服务端，以发送和接收数据
 * 3. 如果连接正常，把灯点亮，如果连接异常，把灯熄灭
 */

#include <ESP8266WiFi.h>

WiFiServer server(80);
WiFiClient client;
boolean alreadyConnected = false;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);

  //初始化LED灯并把灯关闭//
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  Serial.print("开始连接...");
  Serial.println("YFRobot");
  WiFi.mode(WIFI_STA);
  WiFi.begin("YFRobot", "yfjqr2015");

  while(WiFi.status()!=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WIFI已经连接");

  server.begin();  
  Serial.print("服务端已启动，IP地址为");
  Serial.println(WiFi.localIP());
  
}

// the loop function runs over and over again forever
void loop() {
  while(!alreadyConnected){
    client = server.available();
    if(client){
      alreadyConnected=true;
      client.flush();
      client.println("Hello***");

      Serial.print("客户端连接...");
      Serial.println(client.remoteIP());
      digitalWrite(LED_BUILTIN, 1);
    }
  }
  if(!client) {
    alreadyConnected=false;
    digitalWrite(LED_BUILTIN, 0);
    return;
  }
  
  String data = "";
  while(client.available()>0){
    data+=char(client.read());
  }
  if(data.length()>0){
    Serial.println(data);
    client.print("Receive: ");
    client.println(data);
  }
}
