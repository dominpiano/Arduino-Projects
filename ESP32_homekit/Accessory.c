#include <Arduino.h>
#include <homekit/types.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>
#include <port.h>

void setLed();

int brightness = 0;
float saturation = 0;
float hue = 0;

bool animOn = false;
bool led_power = false; //true or flase

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

void led_update() {
  setLed();
  
}

void accessory_init() {
  led_update();
}

//LED ON 
homekit_value_t led_on_get() {
  return HOMEKIT_BOOL(led_power);
}
void led_on_set(homekit_value_t value) {
 if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  led_power = value.bool_value;
  if (led_power) {
    if(brightness == 0){
      brightness = 100;
    }
  }else{
    brightness = 0;
  }
  led_update();
}

//LED BRIGHTNESS
homekit_value_t light_bri_get() {
  return HOMEKIT_INT(brightness);
}
void led_bri_set(homekit_value_t value) {
  if (value.format != homekit_format_int) {
    return;
  }
  brightness = value.int_value;
  led_update();
}

//LED HUE
void led_hue_set(homekit_value_t value) {
  if (value.format != homekit_format_float) {
    return;
  }
  if(animOn){
    animOn = false;
  }
  hue = value.float_value;
  led_update();
}

//LED SATURATION
void led_sat_set(homekit_value_t value) {
  if (value.format != homekit_format_float) {
    return;
  }
  saturation = value.float_value / (float) 100;
  led_update();
}

//SWITCH ON
homekit_value_t anim_on_get() {
  return HOMEKIT_BOOL(animOn);
}
void anim_on_set(homekit_value_t value){
  if (value.format != homekit_format_bool) {
    //printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  if(value.bool_value){
    animOn = true;
  }else{
    animOn = false;
  }
}


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "LED Light"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Dominpiano"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Led"),
            HOMEKIT_CHARACTERISTIC(ON, false, .getter=led_on_get, .setter=led_on_set),
            HOMEKIT_CHARACTERISTIC(HUE, (float) 0, .setter=led_hue_set),
            HOMEKIT_CHARACTERISTIC(BRIGHTNESS, 100, .getter=light_bri_get, .setter=led_bri_set),
            HOMEKIT_CHARACTERISTIC(SATURATION, (float) 0, .setter=led_sat_set),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=2, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Animation Switch"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch"),
            HOMEKIT_CHARACTERISTIC(ON, false, .getter=anim_on_get, .setter=anim_on_set),
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"
};
