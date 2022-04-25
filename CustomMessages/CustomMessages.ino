#include "MCreatorLink.h"
#include <FastLED.h>

#define LED_PIN    4
#define NUM_LEDS   18
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int brightness = 50;

void dataEvent(String command) {
  if(command.equals("red")) {
    for(int x = 0; x < NUM_LEDS; x++){
      leds[x] = CRGB(255,0,0);
    }
    FastLED.show();
  }
  if(command.equals("green")) {
    for(int x = 0; x < NUM_LEDS; x++){
      leds[x] = CRGB(0,255,0);
    }
    FastLED.show();
  }
  if(command.equals("blue")) {
    for(int x = 0; x < NUM_LEDS; x++){
      leds[x] = CRGB(0,0,255);
    }
    FastLED.show();
  }
  if(command.equals("off")) {
    for(int x = 0; x < NUM_LEDS; x++){
      leds[x] = CRGB(0,0,0);
    }
    FastLED.show();
  }
}

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(20);
    MCreatorLink.setup(Serial, "Device Name");
    MCreatorLink.setListener(dataEvent);
    FastLED.addLeds<LED_TYPE,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
    for(int x = 0; x < NUM_LEDS; x++){
      leds[x] = CRGB(0,0,0);
    }
    FastLED.show();
}

void loop() {
    MCreatorLink.loop();
}
