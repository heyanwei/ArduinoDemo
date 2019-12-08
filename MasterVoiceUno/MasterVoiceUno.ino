/*
 * Name: Wilson
 * Description: 
 * 1. 用于初步的测试
 * 2. 建立服务端，以发送和接收数据
 * 3. 如果连接正常，把灯点亮，如果连接异常，把灯熄灭
 */

const int echoPin = 6;
const int trigPin = 7;
const int ledPin = 5;

struct SerialMsg{
  unsigned short header;
  unsigned short len;
  unsigned int distance1;
  unsigned int distance2;
  unsigned int distance3;
  unsigned short tail; 
};

bool isLightOn = false;
int onCount = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200, SERIAL_8E2);//波特率115200，数据位8，偶校验，停止位2
  //Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void SendDistanceMsg(long distance){

  unsigned int dist1=distance;
  struct SerialMsg msg;
  msg.header=0x6666;
  msg.len=sizeof(SerialMsg);
  msg.distance1 = dist1;
  msg.distance2 = 0;
  msg.distance3 = 0;
  msg.tail = 0x8888;
  
  unsigned char sendCs[50];
  memcpy(sendCs, &msg, sizeof(SerialMsg));
  Serial.write(sendCs, sizeof(SerialMsg));
  //Serial.println(distance);
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

  delay(300);
}

// the loop function runs over and over again forever
void loop() {
  CalcDistance();
}
