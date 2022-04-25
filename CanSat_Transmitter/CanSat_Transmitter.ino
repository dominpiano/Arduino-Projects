#include <RadioLib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU6050_tockn.h>
#include <TinyGPS++.h>


TinyGPSPlus gps;
Adafruit_BME280 bme;
MPU6050 mpu6050(Wire);
int refPressure;
int counter = 0;
String lat;
String lng;
String alt;

float latitude;
float longitude;

unsigned char buffer[64];
int count = 0;

SX1278 lora = new Module(5, 35, 4, 34);

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  //   LORA SETUP
  Serial.print(F("[SX1278] Initializing ... "));
  lora.setCurrentLimit(230);
  lora.setSpreadingFactor(12);
  lora.setFrequency(433.5);
  int state = lora.begin();
  
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }


  //   BME SETUP
  bme.begin();
  refPressure = bme.readPressure();


  //  MPU6050 SETUP
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  //  GPS
  Serial2.begin(9600, SERIAL_8N1, 16, 17);


}


void loop() {


  // BME
  int readPressure = bme.readPressure();
  int altitude = (refPressure - readPressure) / 11.3;
  alt = String(altitude);
  float temperature = bme.readTemperature();

  //MPU5060
  mpu6050.update();
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();

  //GPS
  while (Serial2.available()) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        lat = String(latitude, 6);
        lng = String(longitude, 6);
      }
    }
  }

  // DATA SEND
  String stringOfData = alt + "a" + String(readPressure / 100.0) + "b" + String(temperature) + "d" + String(angleX) + "e" + String(angleY) + "f" + lat + "g" + lng;
  byte dataArr[] = {altitude, 0x61, (readPressure / 100.0), 0x62, temperature, 0x63, angleX, 0x64, angleY, 0x65, latitude, 0x66, longitude};
  Serial.println(stringOfData);
  lora.transmit(dataArr, 8);
  //Serial.println("Latitude: " + lat + '\n' + "Longitude: " + lng + '\n' + "https://maps.google.com/?q="+lat+","+lng);

  counter++;

}
