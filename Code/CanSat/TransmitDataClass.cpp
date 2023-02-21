/// TransmitDataClass.cpp
#include "TransmitDataClass.h"

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);
TransmitDataClass::TransmitDataClass(){
  stateBMP280 = false;
  stateMPU6050 = false;
  stateGPS = false;
  stateLM35 = false;
  stateSE014 = false;
  statePixy - false;
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
  if(stateMPU6050 == true){
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
  switch(stateHM330){
    case NO_ERROR:
      for(int i=1;i<=lengthHM330;i++){
        //TODO wartości danych
        frame.print(HM330Value[i]);
        frame.print(";");
        SerialUSB.print(HM330Value[i]);
        SerialUSB.print(";");
      } 
      break;
    default:
      for(int i=1;i<=lengthHM330;i++){
        //TODO wartości danych
        frame.print("failed");
        frame.print(";");
        SerialUSB.print("failed");
        SerialUSB.print(";");
      } 
      break;
  }
  SerialUSB.print(Halla);
  frame.println(Halla);
  radio.transmit(frame);
  frame.clear();
}

void TransmitDataClass::initTransmitDataClass(){
  radio.begin();
  stateBMP280 = initBMP();
  stateMPU6050 = initMPU6050();
  stateSE014 = true; //analogowe nie ma opcji sprawdzenia
  statePixy = initPixy();
  setupSE014();
  stateHM330 = initHM330();
  setupLM35();
  setupGPS();
}
void TransmitDataClass::getTransmitDataClass(){
  if(stateBMP280){
    getBMPData();
  }
  else{
    stateBMP280 = initBMP();
  }
  if(stateMPU6050){
    getMPU6050Data();
  }
  else{
    stateMPU6050 = initMPU6050();
  }
  switch(stateHM330){
    case NO_ERROR:
      getHM330Data();
      break;
    default:
       stateHM330 = initHM330();
      break;
  }
  if(statePixy){
    getPixyData();
  }
  else{
    statePixy = initPixy();
  }
  getSE014Data(); // default 0
  getLM35Data();
  getGPSData();
}
void TransmitDataClass::printTransmitDataClass(){
    printBMPValue();
    printMPU6050Value();
    printHM330();
    printSE014Value();
    printPixyValue();
    printLM35Value();
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
  if(accelgyro.testConnection()) {
    // if connection failed - print message to the user
    SerialUSB.println("MPU6050 connect OK");
    setupMPU6050();
    return true;
    // the program will be 'halted' here and nothing will happen till restart
  } else {
    // print message to the user if everything is OK
    SerialUSB.println("MPU6050 connect failed");
    return false;
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
HM330XErrorCode TransmitDataClass::initHM330() {
  return sensor.init();
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
bool TransmitDataClass::initPixy(){
  if(pixy.init()==PIXY_RESULT_OK){
    return true;
  }
  else{
    return false;
  }
}
void TransmitDataClass::getPixyData(){
  pixy.ccc.getBlocks();
}
void TransmitDataClass::printPixyValue(){
  SerialUSB.println(pixy.ccc.numBlocks);
}
float TransmitDataClass::lm35_raw_to_temperature(int raw) {
  float voltage = raw * 5 / (std::pow(2, 12));
  float assap = 100.0 * voltage;
  return assap;
}
void TransmitDataClass::setupLM35(){
  analogReadResolution(12);
}
void TransmitDataClass::getLM35Data(){
  int raw = analogRead(lm35_pin);
  temperature = lm35_raw_to_temperature(raw);
}
void TransmitDataClass::printLM35Value(){
  SerialUSB.println(temperature);
}
void TransmitDataClass::setupGPS(){
  Serial1.begin(9600);
  SerialUSB.println("Software Serial GPS Test Echo Test");
  Serial1.println(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  Serial1.println(PMTK_SET_NMEA_UPDATE_1HZ);
  SerialUSB.println("Get version!");
  Serial1.println(PMTK_Q_RELEASE);
}
void TransmitDataClass::getGPSData(){
if (Serial1.available()) {
    char c = Serial1.read();
    SerialUSB.write(c);
  }  
}