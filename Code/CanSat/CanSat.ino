// main code: CanSat.ino
#include "TransmitDataClass.h"
  TransmitDataClass testObject;

void setup() {
  SerialUSB.begin(115200);
  testObject.initTransmitDataClass();
  
}

void loop() {
  testObject.getTransmitDataClass();
  testObject.transmitTransmitDataClass();
  //testObject.printTransmitDataClass();
  SerialUSB.println("Witaj Świecie");
  delay(200);
}