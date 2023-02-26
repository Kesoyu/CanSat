// main code: CanSat.ino
#include "TransmitDataClass.h"
#include "softwareStateEnum.cpp"
#include <Adafruit_GPS.h>
// Connect to the GPS on the hardware port

#define GPSSerial Serial

softwareState state = wait;

TransmitDataClass testObject;

#define GPSSerial Serial

Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO false

void setup() {
  SerialUSB.begin(115200);
  testObject.initTransmitDataClass();
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  
  GPSSerial.println(PMTK_Q_RELEASE); // Ask for firmware version
}

uint32_t timer = millis();

void loop() {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) SerialUSB.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    //SerialUSB.print(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 1000) {
    timer = millis(); // reset the timer
    if (GPS.fix) {
      testObject.setGPSData(GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds, GPS.year, GPS.month, GPS.day, GPS.fix, GPS.fixquality, GPS.latitude, GPS.longitude, GPS.lat, GPS.lon, GPS.speed, GPS.angle, GPS.altitude, GPS.satellites, GPS.antenna);
    }
    switch(state) {
      case wait:
        //testObject.getTransmitDataClass();
        //testObject.transmitTransmitDataClass();
        //testObject.printTransmitDataClass();
        state = action;
        break;
      case action:
        testObject.getTransmitDataClass();
        testObject.transmitTransmitDataClass();
        //testObject.printTransmitDataClass();
        //testObject.printMPU6050Value();
        //testObject.calcMPU6050Error();
        //testObject.getMPU6050Data();
        //state = recovery;
        break;
      case recovery:
        //SerialUSB.println(state);
        state = wait;
        break;
    }
  }
  SerialUSB.println("Witaj Świecie");
  delay(1000);
}