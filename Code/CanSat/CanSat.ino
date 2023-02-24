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
    testObject.getTransmitDataClass();
    testObject.transmitTransmitDataClass();
    testObject.printTransmitDataClass();
    state = action;
    delay(1000);
    break;
  case action:
    testObject.getTransmitDataClass();
    testObject.transmitTransmitDataClass();
    testObject.printTransmitDataClass();
    delay(1000);
    state = recovery;
    break;
  case recovery:
    SerialUSB.println(state);
    state = wait;
    break;
}
  SerialUSB.println("Witaj Świecie");
  delay(1000);
}