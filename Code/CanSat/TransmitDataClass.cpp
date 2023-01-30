/// TransmitDataClass.cpp
#include "TransmitDataClass.h"


bool TransmitDataClass::initBMP() {
  if(!bmp.begin()) {
    // if connection failed - print message to the user
    return false;
    // the program will be 'halted' here and nothing will happen till restart
    while(1);
  } else {
    // print message to the user if everything is OK
    return true;
  }
}
  
void TransmitDataClass::setBMP(int value) {
  // possible values of setOversampling:
  //  1 -- 2.62 Pa
  //  2 -- 1.31 Pa
  //  4 -- 0.66 Pa
  //  8 -- 0.33 Pa
  // 16 -- 0.16 Pa 
  bmp.setOversampling(value);
}

double TransmitDataClass::getBMPPressure() {
  double T, P;
  bmp.measureTemperatureAndPressure(T, P);
  return P;
}

void TransmitDataClass::setupMPU6050() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
}

bool TransmitDataClass::initMPU6050() {
  accelgyro.initialize();
  if(!accelgyro.testConnection()) {
    // if connection failed - print message to the user
    return false;
    // the program will be 'halted' here and nothing will happen till restart
    while(1);
  } else {
    // print message to the user if everything is OK
    return true;
  }
}
void TransmitDataClass::getMPU6050Value(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}
void TransmitDataClass::printMPU6050Value(){
  #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        SerialUSB.print("a/g:\t");
        SerialUSB.print(ax); SerialUSB.print("\t");
        SerialUSB.print(ay); SerialUSB.print("\t");
        SerialUSB.print(az); SerialUSB.print("\t");
        SerialUSB.print(gx); SerialUSB.print("\t");
        SerialUSB.print(gy); SerialUSB.print("\t");
        SerialUSB.println(gz);
    #endif
}
bool TransmitDataClass::initHM330() {
  if(sensor.init()) {
    // if connection failed - print message to the user
    return false;
    // the program will be 'halted' here and nothing will happen till restart
    while(1);
  } else {
    // print message to the user if everything is OK
    return true;
  }
}
HM330XErrorCode TransmitDataClass::print_result(const char* str, uint16_t value) {
    if (NULL == str) {
        return ERROR_PARAM;
    }
    SerialUSB.print(str);
    //TODO wartości danych
    SerialUSB.println(value);
    return NO_ERROR;
}

/*parse buf with 29 uint8_t-data*/
HM330XErrorCode TransmitDataClass::parse_result(uint8_t* data) {
    uint16_t value = 0;
    if (NULL == data) {
        return ERROR_PARAM;
    }
    for (int i = 1; i < 8; i++) {
        value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
        print_result(str[i - 1], value);

    }

    return NO_ERROR;
}

HM330XErrorCode TransmitDataClass::parse_result_value(uint8_t* data) {
    if (NULL == data) {
        return ERROR_PARAM;
    }
    /*
    for (int i = 0; i < 28; i++) {
        SerialUSB.print(data[i], HEX);
        SerialUSB.print("  ");
        if ((0 == (i) % 5) || (0 == i)) {
            SerialUSB.println("");
        }
    }
    */
    uint8_t sum = 0;
    for (int i = 0; i < 28; i++) {
        sum += data[i];
    }
    if (sum != data[28]) {
        SerialUSB.println("wrong checkSum!!");
    }
    SerialUSB.println("");
    return NO_ERROR;
}
void TransmitDataClass::printHM330(){
  if (sensor.read_sensor_value(buf, 29)) {
        SERIAL_OUTPUT.println("HM330X read result failed!!");
    }
    parse_result_value(buf);
    parse_result(buf);
    SERIAL_OUTPUT.println("");
}