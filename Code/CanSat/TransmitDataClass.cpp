/// TransmitDataClass.cpp
#include "TransmitDataClass.h"
//Region RadioInit
  Radio radio(Pins::Radio::ChipSelect,
              Pins::Radio::DIO0,
              433.0,
              Bandwidth_125000_Hz,
              SpreadingFactor_9,
              CodingRate_4_8);
//End RadioInit

//Region Constructor
  TransmitDataClass::TransmitDataClass(){
    stateBMP280 = false;
    stateMPU6050 = false;
    stateGPS = false;
    stateLM35 = false;
    stateSE014 = false;
    statePixy = false;
  }
//End Constructor

//Region Transmit
  void TransmitDataClass::transmitTransmitDataClass(){
    if(stateBMP280){
      frame.print(T);
      frame.print(";");
      frame.print(P);
      frame.print(";");
      SerialUSB.print("Temp: ");
      SerialUSB.print(T);
      SerialUSB.print(";");
      SerialUSB.print("hPa: ");
      SerialUSB.print(P);
      SerialUSB.print(";");
    }
    else{
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      SerialUSB.print("Temp: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("hPa: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
    }
    SerialUSB.println();
    if(stateLM35){
      frame.print(temperature);
      frame.print(";");
      SerialUSB.print("Temp: ");
      SerialUSB.print(temperature);
      SerialUSB.print(";");
    }
    else{
      frame.print("failed");
      frame.print(";");
      SerialUSB.print("Temp: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
    }
    SerialUSB.println();
    if(stateMPU6050 == true){
      frame.print(AccX);
      frame.print(";");
      frame.print(AccY);
      frame.print(";");
      frame.print(AccZ);
      frame.print(";");
      frame.print(yaw);
      frame.print(";");
      frame.print(roll);
      frame.print(";");
      frame.print(pitch);
      frame.print(";");

      SerialUSB.print("AccX: ");
      SerialUSB.print(AccX);
      SerialUSB.print(";");
      SerialUSB.print("AccY: ");
      SerialUSB.print(AccY);
      SerialUSB.print(";");
      SerialUSB.print("AccZ: ");
      SerialUSB.print(AccZ);
      SerialUSB.print(";");
      SerialUSB.print("yaw: ");
      SerialUSB.print(yaw);
      SerialUSB.print(";");
      SerialUSB.print("roll: ");
      SerialUSB.print(roll);
      SerialUSB.print(";");
      SerialUSB.print("pitch: ");
      SerialUSB.print(pitch);
      SerialUSB.print(";");
    }
    else{
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");

      SerialUSB.print("AccX: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("AccY: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("AccZ: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("yaw: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("roll: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("pitch: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
    }
    SerialUSB.println();
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
    SerialUSB.println();
    SerialUSB.print("Halla: ");
    SerialUSB.print(Halla);
    SerialUSB.println();
    frame.print(Halla);
    frame.print(";");
    if(stateGPS){
      frame.print(hour);
      frame.print(";");
      frame.print(minute);
      frame.print(";");
      frame.print(seconds);
      frame.print(";");
      frame.print(year);
      frame.print(";");
      frame.print(month);
      frame.print(";");
      frame.print(day);
      frame.print(";");
      frame.print(latitude);
      frame.print(";");
      frame.print(longitude);
      frame.print(";");
      frame.print(lat);
      frame.print(";");
      frame.print(lon);
      frame.print(";");
      frame.print(altitude);
      frame.print(";");
      frame.println(antenna);


      SerialUSB.print("hour: ");
      SerialUSB.print(hour);
      SerialUSB.print(";");
      SerialUSB.print("minute: ");
      SerialUSB.print(minute);
      SerialUSB.print(";");
      SerialUSB.print("seconds: ");
      SerialUSB.print(seconds);
      SerialUSB.print(";");
      SerialUSB.print("year: ");
      SerialUSB.print(year);
      SerialUSB.print(";");
      SerialUSB.print("month: ");
      SerialUSB.print(month);
      SerialUSB.print(";");
      SerialUSB.print("day: ");
      SerialUSB.print(day);
      SerialUSB.print(";");
      SerialUSB.print("latitude: ");
      SerialUSB.print(latitude);
      SerialUSB.print(";");
      SerialUSB.print("longitude: ");
      SerialUSB.print(longitude);
      SerialUSB.print(";");
      SerialUSB.print("lat: ");
      SerialUSB.print(lat);
      SerialUSB.print(";");
      SerialUSB.print("lon: ");
      SerialUSB.print(lon);
      SerialUSB.print(";");
      SerialUSB.print("altitude: ");
      SerialUSB.print(altitude);
      SerialUSB.print(";");
      SerialUSB.print("antenna: ");
      SerialUSB.print(antenna);
      SerialUSB.println(";");
    }
    else{
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.print("failed");
      frame.print(";");
      frame.println("failed");


      SerialUSB.print("hour: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("minute: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("seconds: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("year: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("month: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("day: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("latitude: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("longitude: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("lat: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("lon: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("altitude: ");
      SerialUSB.print("failed");
      SerialUSB.print(";");
      SerialUSB.print("antenna: ");
      SerialUSB.print("failed");
      SerialUSB.println(";");
    }
    
    radio.transmit(frame);
    frame.clear();
  }
//End Transmit

//Region init
  void TransmitDataClass::initTransmitDataClass(){
    radio.begin();
    stateBMP280 = initBMP();
    stateMPU6050 = initMPU6050();
    stateSE014 = true;
    //statePixy = initPixy();
    setupSE014();
    stateHM330 = initHM330();
    setupLM35();
    stateLM35 = true;
  }
//End init

//Region GetData
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
    // if(statePixy){
    //   getPixyData();
    // }
    // else{
    //   statePixy = initPixy();
    // }
    getSE014Data(); // default 0
    getLM35Data();
  }
//End GetData

//Region PrintData
  void TransmitDataClass::printTransmitDataClass(){
      printBMPValue();
      printMPU6050Value();
      printHM330();
      printSE014Value();
      //printPixyValue();
      printLM35Value();
  }
//End PrintData

//Region PrintCSV
  void TransmitDataClass::printCSV(){
    SerialUSB.println("there should be csv printed");
  }
//End PrintCSV

//Region BMP280 ///Czujnik ciśnienia atmosferycznego
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

  void TransmitDataClass::getBMPData() {
    bmp.measureTemperatureAndPressure(T, P);
  }

  void TransmitDataClass::printBMPValue(){
    // print also value of pressure with two decimal places
    SerialUSB.print(P, 2);
    // print units - in this case the library returns hPa
    SerialUSB.println(" hPa");
    SerialUSB.print(T, 2);
    SerialUSB.println(" C");
  }
//End BMP280

//Region MPU6050 ///Moduł 3-osiowego akcelometru i skoroskopu
  void TransmitDataClass::setupMPU6050() {
    //accelgyro.CalibrateGyro();
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
  // void TransmitDataClass::getMPU6050Data(){
  //   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // }
  void TransmitDataClass::calcMPU6050Error(){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    AccX = (float)ax;
    AccY = (float)ay;
    AccZ = (float)az;
    GyroX = (float)gx;
    GyroY = (float)gy;
    GyroZ = (float)gz;
    SerialUSB.print("AccX: ");
    SerialUSB.println(AccX);
    SerialUSB.print("AccY: ");
    SerialUSB.println(AccY);
    SerialUSB.print("AccZ: ");
    SerialUSB.println(AccZ);
    SerialUSB.print("GyroX: ");
    SerialUSB.println(GyroX);
    SerialUSB.print("GyroY: ");
    SerialUSB.println(GyroY);
    SerialUSB.print("GyroZ: ");
    SerialUSB.println(GyroZ);
    double valueOne;
    double valueSecond;
    while (c < 5000) {
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      AccX = (float)ax;
      AccY = (float)ay;
      AccZ = (float)az;
      AccX = AccX / 16384.0 ;
      AccY = AccY / 16384.0 ;
      AccZ = AccZ / 16384.0 ;
      float XFirstStep = pow((AccX), 2);
      float XSecondStep =pow((AccZ), 2);
      double XThirdStep =sqrt(((double)XFirstStep)+((double)XSecondStep));
      double XFourthStep = XThirdStep * 180 / PI;
      double XFifthStep = (((double)AccY) / XFourthStep);
      double XSixthStep = atan(XFifthStep);
      AccErrorX = AccErrorX + XSixthStep;
      // SerialUSB.print("XFirstStep: ");
      // SerialUSB.println(XFirstStep);
      // SerialUSB.print("XSecondStep: ");
      // SerialUSB.println(XSecondStep);
      // SerialUSB.print("XThirdStep: ");
      // SerialUSB.println(XThirdStep);
      // SerialUSB.print("XFourthStep: ");
      // SerialUSB.println(XFourthStep);
      // SerialUSB.print("XFifthStep: ");
      // SerialUSB.println(XFifthStep);
      // SerialUSB.print("XSixthStep: ");
      // SerialUSB.println(XSixthStep);
      // SerialUSB.print("AccErrorX: ");
      // SerialUSB.println(AccErrorX);
      // SerialUSB.print("AccX: ");
      // SerialUSB.println(AccX);
      float YFirstStep = pow((AccY), 2);
      float YSecondStep =pow((AccZ), 2);
      double YThirdStep =sqrt(((double)YFirstStep)+((double)YSecondStep));
      double YFourthStep = YThirdStep * 180 / PI;
      double YFifthStep = (-1 * ((double)AccX) / YFourthStep);
      double YSixthStep = atan(YFifthStep);
      AccErrorY = AccErrorY + YSixthStep;
      // SerialUSB.print("YFirstStep: ");
      // SerialUSB.println(YFirstStep);
      // SerialUSB.print("YSecondStep: ");
      // SerialUSB.println(YSecondStep);
      // SerialUSB.print("YThirdStep: ");
      // SerialUSB.println(YThirdStep);
      // SerialUSB.print("YFourthStep: ");
      // SerialUSB.println(YFourthStep);
      // SerialUSB.print("YFifthStep: ");
      // SerialUSB.println(YFifthStep);
      // SerialUSB.print("YSixthStep: ");
      // SerialUSB.println(YSixthStep);
      // SerialUSB.print("AccErrorY: ");
      // SerialUSB.println(AccErrorY);
      // SerialUSB.print("AccY: ");
      // SerialUSB.println(AccY);
      c++;
    }
    AccErrorX = AccErrorX / 5000;
    AccErrorY = AccErrorY / 5000;
    c = 0;
    // Read gyro values 200 times
    while (c < 5000) {
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      GyroX = (float)gx;
      GyroY = (float)gy;
      GyroZ = (float)gz;
      GyroErrorX = GyroErrorX + (GyroX / 131.0);
      GyroErrorY = GyroErrorY + (GyroY / 131.0);
      GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
      c++;
    }
    c = 0;
    //Divide the sum by 200 to get the error value
    GyroErrorX = GyroErrorX / 5000;
    GyroErrorY = GyroErrorY / 5000;
    GyroErrorZ = GyroErrorZ / 5000;
    // Print the error values on the Serial Monitor
    SerialUSB.print("GyroErrorX: "); ///-5.59
    SerialUSB.println(GyroErrorX); ///-0.27
    SerialUSB.print("GyroErrorY: "); ///-1.79
    SerialUSB.println(GyroErrorY);
    SerialUSB.print("GyroErrorZ: ");
    SerialUSB.println(GyroErrorZ);
    SerialUSB.print("AccErrorX: ");
    SerialUSB.println(AccErrorX);
    SerialUSB.print("AccErrorY: ");
    SerialUSB.println(AccErrorY);
    //delay(30000);
  }
  void TransmitDataClass::getMPU6050Data(){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    AccX = (float)ax;
    AccY = (float)ay;
    AccZ = (float)az;
    AccX = AccX / 16384.0;
    AccY = AccY / 16384.0;
    AccZ = AccZ / 16384.0;
    AccZ = AccZ + 0.97;
    GyroX = (float)gx;
    GyroY = (float)gy;
    GyroZ = (float)gz;
    GyroX = GyroX / 131.0;
    GyroY = GyroY / 131.0;
    GyroZ = GyroZ / 131.0;
    GyroX = GyroX + 5.72; // GyroErrorX ~(-5.59)
    GyroY = GyroY + 0.27; // GyroErrorY ~(-0,27)
    GyroZ = GyroZ + 1.79; // GyroErrorZ ~ (-1.79)
    // SerialUSB.print("AccX: ");
    // SerialUSB.println(AccX);
    // SerialUSB.print("AccY: ");
    // SerialUSB.println(AccY);
    // SerialUSB.print("AccZ: ");
    // SerialUSB.println(AccZ);
    // SerialUSB.print("GyroX: ");
    // SerialUSB.println(GyroX);
    // SerialUSB.print("GyroY: ");
    // SerialUSB.println(GyroY);
    // SerialUSB.print("GyroZ: ");
    // SerialUSB.println(GyroZ);
    previousTime = currentTime;        // Previous time is stored before the actual time read
    currentTime = millis();            // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
    gyroAngleX = GyroX * elapsedTime; // deg/s * s = deg
    gyroAngleY = GyroY * elapsedTime;
    yaw = GyroZ * elapsedTime;
    roll = 1 * gyroAngleX;
    pitch = 1 * gyroAngleY;
    // SerialUSB.print(roll);
    // SerialUSB.print("/");
    // SerialUSB.print(pitch);
    // SerialUSB.print("/");
    // SerialUSB.println(yaw);
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
//End MPU6050

//Region HM330 ///Czujnik zanieczyszczeń PM;1;2.5;10
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
          return ERROR_PARAM;
      }
      //SerialUSB.println("");
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
      SerialUSB.println("HM330X read result failed!!");
    }
    if(parse_result_value(buf)==ERROR_PARAM){
      for(int i=0;i<lengthHM330;i++){
        HM330Value[i]=0;
      }
    }
    if(parse_result(buf)==ERROR_PARAM){
      for(int i=0;i<lengthHM330;i++){
        HM330Value[i]=0;
      }
    }
      //SerialUSB.println("");
  }
//End HM330

//Region SE014 ///Czujnik Halla wzrostowy
  void TransmitDataClass::setupSE014(){
    pinMode(SE014, INPUT);
  }
  void TransmitDataClass::getSE014Data(){
    Halla = digitalRead(SE014);
  }
  void TransmitDataClass::printSE014Value(){
    SerialUSB.println(Halla);
  }
//End SE014

//Region Pixy ///Kamera
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
//End Pixy

//Region LM35 //Termometr analogowy
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
//End LM35

//Region GPS ///moduł GPS PA1616D/MTK3333
  void TransmitDataClass::setGPSData(uint8_t godzina = 0,           ///< GMT hours
                                     uint8_t minuta = 0,         ///< GMT minutes
                                     uint8_t sekunda = 0,        ///< GMT seconds
                                     uint16_t milisekunda = 0,  ///< GMT milliseconds
                                     uint8_t rok = 0,           ///< GMT year
                                     uint8_t miesiac = 0,          ///< GMT month
                                     uint8_t dzien = 0,            ///< GMT day
                                     bool zasieg = false,           ///< Have a fix?
                                     uint8_t jakoszasiegu = 0,     ///< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
                                     float szerokosc = 0,         ///< Floating point latitude value in degrees/minutes
                                     float dlugosc = 0,        ///< Floating point longitude value in degrees/minutes
                                     char szerznak = 'X',             ///< N/S
                                     char dlznak = 'X',             ///< E/W
                                     float predkosc = 0,            ///< Current speed over ground in knots
                                     float katy = 0,            ///< Course in degrees from true north
                                     float wysokosc = 0,           ///< Altitude in meters above MSL
                                     uint8_t satelity = 0,       ///< Number of satellites in use
                                     uint8_t anteny = 0){         ///< Antenna that is used (from PGTOP));    ///< Get GPS Data
    hour = godzina;
    minute = minuta;
    seconds = sekunda;
    milliseconds = milisekunda;
    year = rok;
    month = miesiac;
    day = dzien;
    fix = zasieg;
    fixquality = jakoszasiegu;
    latitude = szerokosc;
    longitude = dlugosc;
    lat = szerznak;
    lon = dlznak;
    speed = predkosc;
    angle = katy;
    altitude = wysokosc;
    satellites = satelity;
    antenna = anteny;
    stateGPS = true;
  }
//End GPS