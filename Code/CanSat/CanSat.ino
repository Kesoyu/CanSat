// main code: CanSat.ino
#include "TransmitDataClass.h"
#include "softwareStateEnum.cpp"
#include <Adafruit_GPS.h>

#define GPSSerial Serial

softwareState state = wait;

TransmitDataClass testObject;

#define GPSSerial Serial

Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO false

void setup() {
  delay(1000);
  Serial.begin(115200);
  testObject.initTransmitDataClass();
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  
  GPSSerial.println(PMTK_Q_RELEASE);
  SerialUSB.println("Setup");
}

uint32_t timer = millis();
int counter = 0;

void loop() {
  char c = GPS.read();

  if (GPSECHO)
    if (c) SerialUSB.print(c);
  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }
  if (millis() - timer > 1000) {
    timer = millis(); // reset the timer
    if (GPS.fix) {
      testObject.setGPSData(GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds, GPS.year, GPS.month, GPS.day, GPS.fix, GPS.fixquality, GPS.latitude, GPS.longitude, GPS.lat, GPS.lon, GPS.speed, GPS.angle, GPS.altitude, GPS.satellites, GPS.antenna);
    }
    switch(state) {
      case wait:
        testObject.getOnlyMPU6050Data();
        testObject.getOnlyBMPData();
        if(testObject.firstPressure-testObject.P>30){
          state = action;
        }
        state = action;
        testObject.transmitTransmitDataClass();
        delay(30000);
        break;
      case action:
        counter++;
        testObject.getTransmitDataClass();
        testObject.transmitTransmitDataClass();
        if(counter==900)
          state = recovery;
        break;
      case recovery:
        testObject.transmitTransmitDataClass();
        delay(30000);
        break;
    }
  }
}