#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int activeR = 0;
int activeG = 0;
int activeB = 0;

float brightness = 0.8;

char mess[10];

int pinR = 25;
int pinG = 26;
int pinB = 27;

int count = 0;

const int ledchannel1 = 0;
const int ledchannel2 = 1;
const int ledchannel3 = 2;
const int freq = 5000;
const int res = 8;

void setup() {
  ledcSetup(ledchannel1, freq, res);
  ledcSetup(ledchannel2, freq, res);
  ledcSetup(ledchannel3, freq, res);
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);
  ledcAttachPin(pinR,ledchannel1);
  ledcAttachPin(pinG,ledchannel2);
  ledcAttachPin(pinB,ledchannel3);
}

void loop() {
  if (SerialBT.available() > 0) {
    char C = SerialBT.read();

     if(C == '.') 
     {
        mess[count] = C;
        String message(mess);
        message = message.substring(0,message.indexOf("."));
        Serial.println(message);
        count = 0;
        
        if (message.startsWith("1")) {
          delay(10);
          String stringR = message.substring(message.indexOf("R") + 1, message.indexOf("G"));
          activeR = stringR.toInt();
          String stringG = message.substring(message.indexOf("G") + 1, message.indexOf("B"));
          activeG = stringG.toInt();
          String stringB = message.substring(message.indexOf("B") + 1, message.indexOf("E"));
          activeB = stringB.toInt();
          activeR = activeR * brightness;
          activeG = activeG * brightness;
          activeB = activeB * brightness;
          ledcWrite(ledchannel1,activeR);
          ledcWrite(ledchannel2,activeG);
          ledcWrite(ledchannel3,activeB);
        }
        else if (message.startsWith("3")){
          String stringBrightness = message.substring(message.indexOf("3") + 1, message.length());
          brightness = stringBrightness.toInt();
          brightness = brightness/100;
          Serial.println(brightness);
          ledcWrite(ledchannel1,activeR * brightness);
          ledcWrite(ledchannel2,activeG * brightness);
          ledcWrite(ledchannel3,activeB * brightness);
        }
     }
     else  mess[count++] = C;
  }
}
