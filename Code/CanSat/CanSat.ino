// main code: CanSat.ino
#include "TransmitDataClass.h"
#include "softwareStateEnum.cpp"

  softwareState state = wait;

  TransmitDataClass testObject;

void setup() {
  SerialUSB.begin(115200);
  testObject.initTransmitDataClass();
  
}

void loop() {
  switch(state) {
  case wait:
    SerialUSB.println(state);
    state = action;
    break;
  case action:
    SerialUSB.println(state);
    state = recovery;
    break;
  case recovery:
    SerialUSB.println(state);
    state = wait;
    break;
}
  testObject.getTransmitDataClass();
  //SerialUSB.println(testObject.stateMPU6050);
  testObject.transmitTransmitDataClass();
  //testObject.printTransmitDataClass();
  SerialUSB.println("Witaj Świecie");
  delay(2000);
}