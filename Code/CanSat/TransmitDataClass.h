/// TransmitDataClass.h
#ifndef TransmitDataClass_h
#define TransmitDataClass_h
#include <Arduino.h>
#include <CanSatKit.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Seeed_HM330X.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#ifdef  ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL_OUTPUT SerialUSB
#else
    #define SERIAL_OUTPUT Serial
#endif

using namespace CanSatKit;

class TransmitDataClass {
  private:
    MPU6050 accelgyro;
    BMP280 bmp;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    #define OUTPUT_READABLE_ACCELGYRO
    HM330X sensor;
  uint8_t buf[30];


  const char* str[7] = {"sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                    };

  public:
    ///BMP SECTOR
    bool initBMP();
    void setBMP(int);
    double getBMPPressure();
    void setupMPU6050();
    bool initMPU6050();
    void getMPU6050Value();
    void printMPU6050Value();
    bool initHM330();
    HM330XErrorCode print_result(const char* str, uint16_t value);
    HM330XErrorCode parse_result(uint8_t* data);
    HM330XErrorCode parse_result_value(uint8_t* data);
    void printHM330();
};

#endif