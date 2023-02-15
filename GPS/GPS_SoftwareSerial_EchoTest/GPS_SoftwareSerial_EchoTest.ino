#include <Adafruit_GPS.h>

#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// turn on GPRMC and GGA
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn on ALL THE DATA
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn off output
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

#define PMTK_Q_RELEASE "$PMTK605*31"

void setup() {

  SerialUSB.begin(115200); // The serial port for the Arduino IDE port output
  Serial1.begin(9600);
  delay(2000);

  SerialUSB.println("Software Serial GPS Test Echo Test");
  // you can send various commands to get it started
  //Serial1.println(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  Serial1.println(PMTK_SET_NMEA_OUTPUT_ALLDATA);

  Serial1.println(PMTK_SET_NMEA_UPDATE_1HZ);

  SerialUSB.println("Get version!");
  Serial1.println(PMTK_Q_RELEASE);
 }


void loop() {
  if (SerialUSB.available()) {
   SerialUSB.println("SerialUSB Available");
   char c = SerialUSB.read();
   SerialUSB.write(c);
   Serial1.write(c);
  }
  if (Serial1.available()) {
    char c = Serial1.read();
    SerialUSB.write(c);
  }
  delay(1000);
}