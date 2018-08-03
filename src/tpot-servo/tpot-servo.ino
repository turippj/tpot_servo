#include <TURIPserver.h>
#include <TURIPserverSPI.h>
#include <TURIPshell.h>
#include <Servo.h>

#define TURIP_MODEL 0x1002
#define TURIP_SERIAL 0x0

#define PIN_SERVO_1 2
#define PIN_SERVO_2 3
#define PIN_SERVO_3 4
#define PIN_SERVO_4 5
#define PIN_SERVO_5 6
#define PIN_SERVO_6 7
#define PIN_SERVO_7 8
#define PIN_SERVO_8 9

Servo Servo1,Servo2,Servo3,Servo4,Servo5,Servo6,Servo7,Servo8;
TURIPport* PortServo1;
TURIPport* PortServo2;
TURIPport* PortServo3;
TURIPport* PortServo4;
TURIPport* PortServo5;
TURIPport* PortServo6;
TURIPport* PortServo7;
TURIPport* PortServo8;

int ServoDeg[8];

void setup() {
  for(int i = 0; i < 8; i++){
    ServoDeg[i] = 90;
  }
  Servo1.attach(PIN_SERVO_1);
  Servo2.attach(PIN_SERVO_2);
  Servo3.attach(PIN_SERVO_3);
  Servo4.attach(PIN_SERVO_4);
  Servo5.attach(PIN_SERVO_5);
  Servo6.attach(PIN_SERVO_6);
  Servo5.attach(PIN_SERVO_7);
  Servo6.attach(PIN_SERVO_8);
  Servo1.write(ServoDeg[0]);
  Servo2.write(ServoDeg[1]);
  Servo3.write(ServoDeg[2]);
  Servo4.write(ServoDeg[3]);
  Servo5.write(ServoDeg[4]);
  Servo6.write(ServoDeg[5]);
  Servo7.write(ServoDeg[6]);
  Servo8.write(ServoDeg[7]);

  Serial.begin(9600);
  TURIPserver.begin(TURIP_MODEL, TURIP_SERIAL);
  TURIPserverSPI.begin();
  PortServo1 = TURIPserver.newPort(1);
  PortServo2 = TURIPserver.newPort(2);
  PortServo3 = TURIPserver.newPort(3);
  PortServo4 = TURIPserver.newPort(4);
  PortServo5 = TURIPserver.newPort(5);
  PortServo6 = TURIPserver.newPort(6);
  PortServo7 = TURIPserver.newPort(7);
  PortServo8 = TURIPserver.newPort(8);

  PortServo1->postReceiveFunc = writeServo1;
  PortServo2->postReceiveFunc = writeServo2;
  PortServo3->postReceiveFunc = writeServo3;
  PortServo4->postReceiveFunc = writeServo4;
  PortServo5->postReceiveFunc = writeServo5;
  PortServo6->postReceiveFunc = writeServo6;
  PortServo7->postReceiveFunc = writeServo7;
  PortServo8->postReceiveFunc = writeServo8;
}

void loop() {
  TURIPserverSPI.update();
  serialEvent();
}

void writeServo1(){
  ServoDeg[0] = constrain(PortServo1->readInt16(), 0, 180);
  PortServo1->writeInt16(ServoDeg[0]);
  Servo1.write(ServoDeg[0]);
}

void writeServo2(){
  ServoDeg[1] = constrain(PortServo2->readInt16(), 0, 180);
  PortServo2->writeInt16(ServoDeg[1]);
  Servo2.write(ServoDeg[1]);
}

void writeServo3(){
  ServoDeg[2] = constrain(PortServo3->readInt16(), 0, 180);
  PortServo3->writeInt16(ServoDeg[2]);
  Servo3.write(ServoDeg[2]);
}

void writeServo4(){
  ServoDeg[3] = constrain(PortServo4->readInt16(), 0, 180);
  PortServo4->writeInt16(ServoDeg[3]);
  Servo4.write(ServoDeg[3]);
}

void writeServo5(){
  ServoDeg[4] = constrain(PortServo5->readInt16(), 0, 180);
  PortServo5->writeInt16(ServoDeg[4]);
  Servo5.write(ServoDeg[4]);
}

void writeServo6(){
  ServoDeg[5] = constrain(PortServo6->readInt16(), 0, 180);
  PortServo6->writeInt16(ServoDeg[5]);
  Servo6.write(ServoDeg[5]);
}

void writeServo7(){
  ServoDeg[6] = constrain(PortServo6->readInt16(), 0, 180);
  PortServo6->writeInt16(ServoDeg[6]);
  Servo6.write(ServoDeg[6]);
}

void writeServo8(){
  ServoDeg[7] = constrain(PortServo6->readInt16(), 0, 180);
  PortServo6->writeInt16(ServoDeg[7]);
  Servo6.write(ServoDeg[7]);
}

void serialEvent(){
  static String strBuf;
  while(Serial.available()){
    char c = Serial.read();
    if(c == 0x0a){  // 0x0a: LF
      strBuf.trim();
      if(strBuf.length() > 0){
        char response[128];
        char request[64];
        strBuf.toCharArray(request, 64);
        TURIPshell(request, response, 127);
        Serial.println(response);
      }
      strBuf = "";
    }else{
      strBuf += c;
    }
  }
}
