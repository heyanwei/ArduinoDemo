/*
 * Name: Wilson
 * Description: 
 * 1. 用于初步的测试
 * 2. 建立服务端，以发送和接收数据
 * 3. 如果连接正常，把灯点亮，如果连接异常，把灯熄灭
 */

#include <ESP8266WiFi.h>

const int echoPin = 12;
const int trigPin = 13;
const int ledPin = 14;

struct SerialMsg{
  unsigned short header;
  unsigned short len;
  unsigned int distance1;
  unsigned int distance2;
  unsigned int distance3;
  unsigned short tail; 
};

WiFiServer server(80);
WiFiClient client;
bool alreadyConnected = false;
bool isLightOn = false;
int onCount = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(ledPin, LOW);

  //Serial.print("开始连接...");
  //Serial.println("YFRobot");
  WiFi.mode(WIFI_STA);
  WiFi.begin("YFRobot", "yfjqr2015");

  while(WiFi.status()!=WL_CONNECTED) {
    CalcDistance();
  }
  //Serial.println();
  //Serial.println("WIFI已经连接");

  server.begin();  
  //Serial.print("服务端已启动，IP地址为");
  //Serial.println(WiFi.localIP());
}

void SendDistanceMsg(long distance){

  unsigned int dist1=distance;
  struct SerialMsg msg;
  msg.header=0x6666;
  msg.len=sizeof(SerialMsg)-2;
  msg.distance1 = dist1;
  msg.distance2 = 0;
  msg.distance3 = 0;
  msg.tail = 0x8888;
  
  unsigned char sendCs[50];
  memcpy(sendCs, &msg, sizeof(SerialMsg));
  Serial.write(sendCs, sizeof(SerialMsg)-2);
}

//测距//
void CalcDistance(){
  long duration = 0;
  long cm = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = duration / 29 / 2;

  if(cm>40){
    digitalWrite(ledPin, LOW);  
  }else{
    digitalWrite(ledPin, HIGH);    
  }

  SendDistanceMsg(cm);
  if(alreadyConnected){
    client.println(cm);
  }

  delay(300);
}

// the loop function runs over and over again forever
void loop() {
  while(!alreadyConnected){
    CalcDistance();
    //Serial.println("Wait Client Connect...");
    client = server.available();
    if(client){
      alreadyConnected=true;
      client.flush();
      client.println("OK***");

      //Serial.print("客户端连接...");
      //Serial.println(client.remoteIP());
    }
  }
  if(!client) {   
    alreadyConnected=false;
    CalcDistance();
    return;
  }

  String data = "";
  while(client.available()>0){
    data+=char(client.read());
  }
  if(data.length()>0){
    //Serial.println(data);
    client.println(data);
  }
  
  CalcDistance();
}
