// main code: CanSat.ino
#include "TransmitDataClass.h"
#include "softwareStateEnum.cpp"
#include <Adafruit_GPS.h>

#define GPSSerial Serial

softwareState state = wait;

TransmitDataClass testObject;

#define GPSSerial Serial

Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO true

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
uint32_t timerWait = millis();
uint32_t timerAction = millis();
uint32_t timerRecovery = millis();

int counterMissons = 0;
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
    timer = millis();
    if (GPS.fix) {
      testObject.setGPSData(GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds, GPS.year, GPS.month, GPS.day, GPS.fix, GPS.fixquality, GPS.latitude, GPS.longitude, GPS.lat, GPS.lon, GPS.speed, GPS.angle, GPS.altitude, GPS.satellites, GPS.antenna);   
    }
    if(state==wait && millis() - timerWait > 5000) {
      timerWait = millis();
      if(counter==0){
        testObject.getOnlyHM330Data();
      }
      testObject.getOnlyBMPData();
      if(testObject.firstPressure-testObject.P>20){
        state = action;
      }
      testObject.transmitTransmitDataClass();
      state = action;
    }
    if(state==action){
      counterMissons++;
      testObject.getTransmitDataClass();
      testObject.transmitTransmitDataClass();
      if(counterMissons>=900){
        state = recovery;
      } 
    }
    if(state==recovery && millis() - timerRecovery > 5000){
      timerRecovery = millis();
      testObject.transmitTransmitDataClass();
    }
  }
  counter++;
}