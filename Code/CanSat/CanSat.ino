// main code: CanSat.ino
#include "TransmitDataClass.h"

TransmitDataClass testObject;

void setup() {
  SerialUSB.begin(115200);
  if(testObject.initBMP()){
    SerialUSB.println("BMP init success!");
  }
  else{
    SerialUSB.println("BMP init failed!");
  }
  testObject.setBMP(16);
  testObject.setupMPU6050();
  if(testObject.initMPU6050()){
    SerialUSB.println("MPU6050 init success!");
  }
  else{
    SerialUSB.println("MPU6050 init failed!");
  }
  if(testObject.initHM330()){
    SerialUSB.println("MPU6050 init success!");
  }
  else{
    SerialUSB.println("MPU6050 init failed!");
  }
}

void loop() {
  float pressureValue = testObject.getBMPPressure();
  SerialUSB.print("Pressure = ");
  // print also value of pressure with two decimal places
  SerialUSB.print(pressureValue, 2);
  // print units - in this case the library returns hPa
  SerialUSB.println(" hPa");
  testObject.getMPU6050Value();
  testObject.printMPU6050Value();
  testObject.printHM330();
  delay(2000);
}