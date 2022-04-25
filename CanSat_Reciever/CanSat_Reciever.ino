#include <RadioLib.h>


SX1278 lora = new Module(5, 35, 4, 36);

// or using RadioShield
// https://github.com/jgromes/RadioShieldM
//SX1278 lora = RadioShield.ModuleA;

void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initializing ... "));
  lora.setSpreadingFactor(12);
  int state = lora.begin();
  
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  //int16_t dane;
  
  
  //int state = lora.receive((uint8_t *)&dane, sizeof(dane));

  String str;
  int state = lora.receive(str);

  if (state == ERR_NONE) {
    String altitude = str.substring(0,str.indexOf("a"));
    String pressure = str.substring(str.indexOf("a") + 1,str.indexOf("b"));
    String temp = str.substring(str.indexOf("b") + 1,str.indexOf("c"));
    String hum = str.substring(str.indexOf("c") + 1,str.indexOf("d"));
    String X = str.substring(str.indexOf("d") + 1,str.indexOf("e"));
    String Y = str.substring(str.indexOf("e") + 1,str.indexOf("f"));
    String p_lat = str.substring(str.indexOf("f") + 1,str.indexOf("g"));
    String p_lng = str.substring(str.indexOf("g") + 1,str.length());
    Serial.println("");
    Serial.println(altitude+" m");
    Serial.println(pressure+" hpa");
    Serial.println(temp+" C");
    Serial.println(hum+" %");
    Serial.println(X+" X");
    Serial.println(Y+" Y");
    Serial.println(p_lat+" lat");
    Serial.println(p_lng+" lng");
    Serial.println(str);
  } 
}
