#include "WiFi.h"
#include "arduino_homekit_server.h"
#include "ESPButton.h"
#include <FastLED.h>
#include "Arduino.h"

#define LED_PIN     26
#define NUM_LEDS    25
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

extern "C" homekit_server_config_t config;
extern "C" void accessory_init();
extern "C" int brightness;
extern "C" float hue;
extern "C" float saturation;
extern "C" void setLed();
extern "C" bool animOn;

float Bri_before = 0;
float Bri = 0;

void setLed(){
    Bri = pow(brightness, 2) / 100;
    smoothBright(Bri_before, Bri);
    Bri_before = Bri;
    setLedColorHSV(hue, (double)saturation, (double)1);
    FastLED.show();
}


void smoothBright(int bri_b, int bri){
    if(bri > bri_b){
        for(int i = bri_b; i <= bri; i++){
            FastLED.setBrightness(i);
            FastLED.show();
            delay(10);
        }
    }else{
        for(int i = bri_b; i >= bri; i--){
            FastLED.setBrightness(i);
            FastLED.show();
            delay(10);
        }
    }
}

#define PIN_BTN 0

const char *ssid = "Agrestowa2,4G";
const char *password = "Dominpiano321!";

void setup() {
	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.persistent(false);
	WiFi.disconnect(false);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);

	printf("\n");
	printf("SketchSize: %d B\n", ESP.getSketchSize());
	printf("FreeSketchSpace: %d B\n", ESP.getFreeSketchSpace());
	printf("FlashChipSize: %d B\n", ESP.getFlashChipSize());
	printf("FlashChipSpeed: %d\n", ESP.getFlashChipSpeed());
	printf("SdkVersion: %s\n", ESP.getSdkVersion());
	printf("FreeHeap: %d B\n", ESP.getFreeHeap()); 
	DEBUG_HEAP();

	//Init Button
	pinMode(PIN_BTN, INPUT_PULLUP);
	ESPButton.add(0, PIN_BTN, LOW, false, true);
	ESPButton.setCallback([](uint8_t id, ESPButtonEvent event) {
		printf("ButtonEvent: %s\n", ESPButton.getButtonEventDescription(event));
		if (event == ESPBUTTONEVENT_SINGLECLICK) {
			//led_toggle();
		} else if (event == ESPBUTTONEVENT_DOUBLECLICK) {

		} else if (event == ESPBUTTONEVENT_LONGCLICK) {
			homekit_storage_reset();
			esp_restart();
		}
	});
	ESPButton.begin();

  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
	homekit_setup();
}

int h = 0;

void loop() {
	ESPButton.loop();
	uint32_t time = millis();
	static uint32_t next_heap_millis = 0;
	if (time > next_heap_millis) {
		INFO("heap: %u, sockets: %d", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
		next_heap_millis = time + 5000;
	}
  if(animOn){
    static uint32_t next_time = 0;
    if(time > next_time){
      setLedColorHSV(h, 1, 1);
      FastLED.show();
      if(h < 360){
        h++;
      }else{
        h = 0;
      }
      next_time = time + 100;
    }
  }
	delay(5);
}

void homekit_setup() {
	accessory_init();
	arduino_homekit_setup(&config);
}

void setLedColorHSV(int h, double s, double v) {

  //this is the algorithm to convert from HSV to RGB
  double R=0; 
  double G=0; 
  double B=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i){
  case 0: //rojo dominante
    R = v;
    G = tv;
    B = pv;
    break;
  case 1: //verde
    R = qv;
    G = v;
    B = pv;
    break;
  case 2: 
    R = pv;
    G = v;
    B = tv;
    break;
  case 3: //azul
    R = pv;
    G = qv;
    B = v;
    break;
  case 4:
    R = tv;
    G = pv;
    B = v;
    break;
  case 5: //rojo
    R = v;
    G = pv;
    B = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red = constrain((int)255*R, 0, 255);
  int green = constrain((int)255*G, 0, 255);
  int blue = constrain((int)255*B, 0, 255);

  for(int a = 0; a < NUM_LEDS; a++){
     leds[a] = CRGB(red, green, blue);
  }
}
