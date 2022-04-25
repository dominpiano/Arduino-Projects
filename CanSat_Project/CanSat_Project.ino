#include <RadioLib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU6050_tockn.h>


Adafruit_BME280 bme;
MPU6050 mpu6050(Wire);
int refPressure;
int counter = 0;

SX1278 lora = new Module(5, 34, 4, 35);

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

//   LORA SETUP
  Serial.print(F("[SX1278] Initializing ... "));
  lora.setCurrentLimit(230);
  lora.setSpreadingFactor(12);
  int state = lora.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }


  //   BME SETUP
  bme.begin(0x76);
  refPressure = bme.readPressure();


  //  MPU6050 SETUP
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
}


void loop() {

  int readPressure = bme.readPressure();
  int altitude = (refPressure - readPressure) / 11.3;
  String string = String(altitude);
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();

  mpu6050.update();
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();

  String stringOfData = String(altitude) + "a" + String(readPressure / 100.0) + "b" + String(temperature) + "c" + String(humidity) + "d" + String(angleX) + "e" + String(angleY) + "f";
  Serial.println(stringOfData);
  lora.transmit(stringOfData);
  delay(500);

  counter++;

}
