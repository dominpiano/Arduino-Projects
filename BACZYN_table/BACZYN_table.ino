#include "BluetoothSerial.h"
#include <FastLED.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;

#define LED_PIN     33
#define NUM_LEDS    10
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

char mess[10];

int count = 0;

int led;
int brightness = 90;

int R;
int G;
int B;
int r = 255;
int g = 0;
int b = 0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("BACZYN TABLICZKA BIBLIOTEKA");
  FastLED.addLeds<LED_TYPE,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  playAuto();
  FastLED.show();

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
          R = stringR.toInt();
          String stringG = message.substring(message.indexOf("G") + 1, message.indexOf("B"));
          G = stringG.toInt();
          String stringB = message.substring(message.indexOf("B") + 1, message.indexOf("E"));
          B = stringB.toInt();
          for(int x = 0;x<10;x++){
            leds[x] = CRGB(R,G,B);
          }
          FastLED.show();
        }
        else if (message.startsWith("3")){
          String stringBrightness = message.substring(message.indexOf("3") + 1, message.length());
          brightness = stringBrightness.toInt();
          FastLED.setBrightness(brightness);
          FastLED.show();
        }
        else if (message.startsWith("4")){
          if(message.substring(message.indexOf("4")+1, message.length()) == "auto"){
              playAuto();
          }
        }
        else if (message.startsWith("5")){
          if(message.substring(message.indexOf("5")+1, message.length()) == "off"){
             for(int h = 0;h<10;h++){
               leds[h] = CRGB(0,0,0);
             }
             FastLED.show();
          }
        }
     }
     else  mess[count++] = C;
  }
}

void playAuto(){
  while(1==1){
    for(int hue=0;hue<360;hue++)
    {
      setLedColorHSV(hue,1,1);
      delay(40);
      if(SerialBT.available()){
        break;
      }
    }
    if(SerialBT.available()){
        break;
      }
  }
}

void setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //red dominance
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //green
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //blue
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //red
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

  for(int a = 0;a<10;a++){
     leds[a] = CRGB(red,green,blue);
  }
  FastLED.show();
}
