/// TransmitDataClass.h
#ifndef TransmitDataClass_h
#define TransmitDataClass_h
#include <Arduino.h>
#include <CanSatKit.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Seeed_HM330X.h>
#include <Pixy2.h>
#include <cmath>
#include <Adafruit_GPS.h>
using namespace CanSatKit;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#ifdef  ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL_OUTPUT SerialUSB
#else
    #define SERIAL_OUTPUT Serial
#endif
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_Q_RELEASE "$PMTK605*31"


class TransmitDataClass {
  private:
    MPU6050 accelgyro;
    BMP280 bmp;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    #define OUTPUT_READABLE_ACCELGYRO
    HM330X sensor;
    uint8_t buf[30];
    double T, P;
    const char* str[7] = {"sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                      };
    static const int lengthHM330=6;
    uint16_t HM330Value[lengthHM330];
    int LM35 = A1;   //pin analogowy A1 połączony z sygnałem z czujnika
    float VOLT;
    float TEMP;
    int SE014 = 5;
    int Halla;
    Pixy2 pixy;
    float temperature;
    Frame frame;
    const int lm35_pin = A0;
  public:
    bool stateBMP280, stateMPU6050, stateLM35, stateGPS, stateSE014;
    HM330XErrorCode stateHM330;
    bool statePixy;
    TransmitDataClass();
    void initTransmitDataClass();
    void getTransmitDataClass();
    void printTransmitDataClass();
    void transmitTransmitDataClass();
    void printCSV();
    ///BMP SECTOR
    bool initBMP();
    void setBMP(int);
    double getBMPData();
    void printBMPValue();
    ///MPU6050 SECTOR
    void setupMPU6050();
    bool initMPU6050();
    void getMPU6050Data();
    void printMPU6050Value();
    ///HM330 SECTOR
    HM330XErrorCode initHM330();
    HM330XErrorCode print_result(const char* str, uint16_t value,int count);
    HM330XErrorCode parse_result(uint8_t* data);
    HM330XErrorCode parse_result_value(uint8_t* data);
    void getHM330Data();
    void printHM330();
    void setupSE014();
    void getSE014Data();
    void printSE014Value();
    bool initPixy();
    void getPixyData();
    void printPixyValue();
    float lm35_raw_to_temperature(int data);
    void setupLM35();
    void getLM35Data();
    void printLM35Value();
    void setupGPS();
    void getGPSData();
};

#endif