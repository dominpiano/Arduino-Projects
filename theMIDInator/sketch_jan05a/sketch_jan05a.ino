#include <FastLED.h>

#define LED_PIN    4
#define NUM_LEDS   8
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int brightness = 50;

int val;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);
  if(val > 0 && val < 10){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[0] = CRGB(10,255,10);
    FastLED.show();
  }
  if(val > 10 && val < 20){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[1] = CRGB(10,255,10);
    FastLED.show();
  }
  if(val > 20 && val < 30){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[2] = CRGB(10,255,10);
    FastLED.show();
  }
  if(val > 30 && val < 40){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[3] = CRGB(10,255,10);
    FastLED.show();
  }
  if(val > 40 && val < 50){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[4] = CRGB(10,255,10);
    FastLED.show();
  }
  if(val > 50 && val < 60){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[5] = CRGB(255,255,0);
    FastLED.show();
  }
  if(val > 60 && val < 70){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[6] = CRGB(255,255,0);
    FastLED.show();
  }
  if(val > 70 && val < 80){
    for(int i = 0; i < 8; i++){
      leds[i] = CRGB(0);
    }
    leds[7] = CRGB(255,0,0);
    FastLED.show();
  }

  delay(50);
}
