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
#include <SPI.h>
#include <SD.h>
using namespace CanSatKit;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_ACCELGYRO

class TransmitDataClass {
  private:
    int index;
    int indexBMP;
    const static int SDPin = 11;
    MPU6050 accelgyro;      ///< Instance of the MPU6050 module
    int16_t ax,             ///< Accelerometer x axis value
    ay,                     ///< Accelerometer y axis value
    az;                     ///< Accelerometer z axis value
    int16_t gx,             ///< Gyroscope x axis value
    gy,                     ///< Gyroscope y axis value
    gz;                     ///< Gyroscope z axis value
    
    float AccX, AccY, AccZ;
    float GyroX, GyroY, GyroZ;
    float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
    float roll, pitch, yaw;
    float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
    float elapsedTime, currentTime, previousTime;
    int c = 0;

      
    BMP280 bmp;         ///< Instance of the BMP280 module

    HM330X sensor;      ///< Instance of the HM330 module
    uint8_t buf[30];    ///< Buffor for a validation a HM330 Data
    
    const char* str[7] = {"sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",     ///< Contains a description of the HM330 displayed values
                      "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",                         
                      "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",                          
                      "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                      };
    static const int lengthHM330=6;     ///< Range of HM330 Values
    uint16_t HM330Value[lengthHM330];   ///< Storage HM330 Value
    
    int SE014 = 5;              ///< SE014 anaolg pin code
    const int lm35_pin = A0;    ///< LM35 anolog pin code
    
    int Halla;              ///< Detecting increased of magnetic field 0:1 values
    Pixy2 pixy;             ///< Pixy UART connection
    const int pixyRes = 65096; ///< Resolutions of pixy camera detection square
    float blue;
    float yellow;
    float green;
    float other;
    int numberOfBlocks;

    float temperature;      ///< Temperature LM35 value
    Frame frame;            ///< Frame for transmit
    

    uint8_t hour;           ///< GMT hours
    uint8_t minute;         ///< GMT minutes
    uint8_t seconds;        ///< GMT seconds
    uint16_t milliseconds;  ///< GMT milliseconds
    uint8_t year;           ///< GMT year
    uint8_t month;          ///< GMT month
    uint8_t day;            ///< GMT day

    bool fix;               ///< Have a fix?
    uint8_t fixquality;     ///< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
    float latitude;         ///< Floating point latitude value in degrees/minutes
                            ///< as received from the GPS (DDMM.MMMM)
    float longitude;        ///< Floating point longitude value in degrees/minutes
                            ///< as received from the GPS (DDDMM.MMMM)
    char lat = 'X';         ///< N/S
    char lon = 'X';         ///< E/W
    float speed;            ///< Current speed over ground in knots
    float angle;            ///< Course in degrees from true north
    float altitude;         ///< Altitude in meters above MSL
    uint8_t satellites;     ///< Number of satellites in use
    uint8_t antenna;        ///< Antenna that is used (from PGTOP)
  public:
    double firstPressure;
    double T                ///< Contains a BMP35 atmospheric pressure value
        , P;                ///< Contains a BMP35 temperature value
    bool stateBMP280, stateMPU6050, stateLM35, stateGPS, stateSE014, stateSD;  ///< status of module
    HM330XErrorCode stateHM330;                                                ///< status of module
    bool statePixy;                                                            ///< status of module

    ///Region Main Functions
      TransmitDataClass();                ///< Main Constructor of the TransmitDataClass
      void initTransmitDataClass();       ///< Contains all module initalization
      void getTransmitDataClass();        ///< Collects all availbe data from modules
      void printTransmitDataClass();      ///< Print all collected data
      void transmitTransmitDataClass();   ///< Transmit a collected data in .csv format
      void printCSV();                    ///< Print all colected data in csv format
    ///End Main Functions

    ///Region BMP280
      bool initBMP();         ///< Initalize BMP280 module
      void setBMP(int);       ///< Setup BMP280 module
      void getBMPData();      ///< Get BMP280 Data
      void getOnlyBMPData();
      void printBMPValue();   ///< Print BMP280 Value
    ///End BMP280

    ///Region MPU6050
      bool initMPU6050();         ///< Initalize MPU6050 module
      void calcMPU6050Error();
      void setupMPU6050();        ///< Setup MPU6050 module
      void getMPU6050Data();      ///< Get and validate MPU6050 Data
      void getOnlyMPU6050Data(); 
      void printMPU6050Value();   ///< Print MPU6050 Value
    ///End MPU6050

    ///Region HM330
      HM330XErrorCode initHM330();                                                  ///< Initalize HM330 module
      HM330XErrorCode print_result(const char* str, uint16_t value,int count);      ///< Print Values with description
      HM330XErrorCode parse_result(uint8_t* data);                                  ///< Parse Result
      HM330XErrorCode parse_result_value(uint8_t* data);                            ///< Parse Result Value

      void getHM330Data();      ///< Get HM330 Data
      void printHM330();        ///< Print HM330 Data
    ///End HM330

    ///Region SE014
      void setupSE014();        ///< Setup SE014
      void getSE014Data();      ///< Get SE014 Data
      void printSE014Value();   ///< Print SE014 Value
    ///End SE014

    ///Region Pixy
      bool initPixy();            ///< Initalize UART Pixy connection
      void getPixyData();         ///< Get Pixy detected blocks
      void calculatePixyArea();   ///< Calculate defined area field
      void printPixyValue();      ///< Print Pixy Values
    ///End Pixy

    ///Region LM35
      float lm35_raw_to_temperature(int data);    ///< Calculate LM35 temperature
      void setupLM35();                           ///< Setup LM35 module
      void getLM35Data();                         ///< Get LM35 Data
      void printLM35Value();                      ///< Print LM35 Value
    ///End LM35

    ///Region GPS     
      void setGPSData(uint8_t, uint8_t, uint8_t, uint16_t,uint8_t,            ///< Intalization and parsing are set in main program
                      uint8_t, uint8_t, bool, uint8_t, float, float,          ///< I have gave up at this part:#
                      char, char, float, float, float, uint8_t, uint8_t);     ///< set GPS Data
    ///End GPS
    ///Region SD     
      bool initSD();    
    ///End SD


};

#endif