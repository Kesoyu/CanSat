/// TransmitDataClass.cpp
#include "TransmitDataClass.h"

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);
TransmitDataClass::TransmitDataClass(){
  stateBMP280 = stateHM330 = stateMPU6050 = stateGPS = stateLM35 = stateSE014 = false;
}

void TransmitDataClass::transmitTransmitDataClass(){
  if(stateBMP280){
    frame.print(T);
    frame.print(";");
    frame.print(P);
    frame.print(";");
    SerialUSB.print(T);
    SerialUSB.print(";");
    SerialUSB.print(P);
    SerialUSB.print(";");
  }
  else{
    frame.print("failed");
    frame.print(";");
    frame.print("failed");
    frame.print(";");
    SerialUSB.print("failed");
    SerialUSB.print(";");
    SerialUSB.print("failed");
    SerialUSB.print(";");
  }
  if(stateMPU6050){
    frame.print(ax);
    frame.print(";");
    frame.print(ay);
    frame.print(";");
    frame.print(az);
    frame.print(";");
    frame.print(gx);
    frame.print(";");
    frame.print(gy);
    frame.print(";");
    frame.print(gz);
    frame.print(";");
    SerialUSB.print(ax);
    SerialUSB.print(";");
    SerialUSB.print(ay);
    SerialUSB.print(";");
    SerialUSB.print(az);
    SerialUSB.print(";");
    SerialUSB.print(gx);
    SerialUSB.print(";");
    SerialUSB.print(gy);
    SerialUSB.print(";");
    SerialUSB.print(gz);
    SerialUSB.print(";");
  }
  else{
    for(int i=0;i<6;i++){
      frame.print("failed");
      frame.print(";");
      SerialUSB.print("failed");
      SerialUSB.print(";");
    }
  }
  for(int i=1;i<=lengthHM330;i++){
    //TODO wartości danych
    frame.print(HM330Value[i]);
    frame.print(";");
    SerialUSB.print(HM330Value[i]);
    SerialUSB.print(";");
  }
  SerialUSB.print("ASDASDASDAd");
  SerialUSB.println(stateHM330);

  frame.print(Halla);
  radio.transmit(frame);
  frame.clear();
}

void TransmitDataClass::initTransmitDataClass(){
  radio.begin();
  stateBMP280 = initBMP();
  stateMPU6050 = initMPU6050();
  stateSE014 = true; //analogowe nie ma opcji sprawdzenia
  setupSE014();
  stateHM330 = initHM330();
}
void TransmitDataClass::getTransmitDataClass(){
  if(stateBMP280){
    getBMPData();
  }
  if(stateMPU6050){
    getMPU6050Data();
  }
  if(!stateHM330){
    getHM330Data();
  }
  getSE014Data(); // default 0
}
void TransmitDataClass::printTransmitDataClass(){
    printBMPValue();
    printMPU6050Value();
    printHM330();
    printSE014Value();
}
bool TransmitDataClass::initBMP() {
  if(!bmp.begin()) {
    // if connection failed - print message to the user
    SerialUSB.println("BMP280 connect failed");
    return false;
    // the program will be 'halted' here and nothing will happen till restart
  } else {
    // print message to the user if everything is OK
    SerialUSB.println("BMP280 connect OK");
    setBMP(16);
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

double TransmitDataClass::getBMPData() {
  bmp.measureTemperatureAndPressure(T, P);
  return P;
}

void TransmitDataClass::printBMPValue(){
  // print also value of pressure with two decimal places
  SerialUSB.print(P, 2);
  // print units - in this case the library returns hPa
  SerialUSB.println(" hPa");
  SerialUSB.print(T, 2);
  SerialUSB.println(" C");
}

void TransmitDataClass::setupMPU6050() {
  accelgyro.CalibrateGyro();
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
    SerialUSB.println("MPU6050 connect failed");
    return false;
    // the program will be 'halted' here and nothing will happen till restart
  } else {
    // print message to the user if everything is OK
    SerialUSB.println("MPU6050 connect OK");
    setupMPU6050();
    return true;
  }
}
void TransmitDataClass::getMPU6050Data(){
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
    SerialUSB.println("HM330 connect OK");
    return true;
    // the program will be 'halted' here and nothing will happen till restart
  } else {
    // print message to the user if everything is OK
    SerialUSB.println("HM330 connect failed");
    return false;
  }
}
HM330XErrorCode TransmitDataClass::print_result(const char* str, uint16_t value, int count) {
    if (NULL == str) {
        return ERROR_PARAM;
    }
    HM330Value[count] = value;
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
        print_result(str[i - 1], value, i-1);

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
  for(int i=1;i<=lengthHM330;i++){
    SerialUSB.print(str[i]);
    //TODO wartości danych
    SerialUSB.println(HM330Value[i]);
  }
}

void TransmitDataClass::getHM330Data(){
  if (sensor.read_sensor_value(buf, 29)) {
        SERIAL_OUTPUT.println("HM330X read result failed!!");
    }
    parse_result_value(buf);
    parse_result(buf);
    SERIAL_OUTPUT.println("");
}

void TransmitDataClass::printCSV(){
  SerialUSB.println("there should be csv printed");
}

void TransmitDataClass::setupSE014(){
  pinMode(SE014, INPUT);
}
void TransmitDataClass::getSE014Data(){
  Halla = digitalRead(SE014);
}
void TransmitDataClass::printSE014Value(){
  SerialUSB.println(Halla);
}