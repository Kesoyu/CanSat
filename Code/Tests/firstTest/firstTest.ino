#include <CanSatKit.h>
//  #include <SPI.h>
//  #include <Pixy2.h>
//  #include <SD.h>

 using namespace CanSatKit;

 //Pixy2 pixy;
 const int chipSelect = 11;

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);

//BMP280 is a pressure sensor, create the sensor object

BMP280 bmp;

Frame frame;

void setup() {
  SerialUSB.begin(115200);

  // use begin() function to check if sensor is conneted and is able to communicate
  // with the CanSat board
  if(!bmp.begin()) {
    // if connection failed - print message to the user
    SerialUSB.println("BMP init failed!");
    // the program will be 'halted' here and nothing will happen till restart
    while(1);
  } else {
    // print message to the user if everything is OK
    SerialUSB.println("BMP init success!");
  }
  
  // setOversampling function allows to set resolution of the pressure sensor
  // possible values of setOversampling:
  //  1 -- 2.62 Pa
  //  2 -- 1.31 Pa
  //  4 -- 0.66 Pa
  //  8 -- 0.33 Pa
  // 16 -- 0.16 Pa 
  bmp.setOversampling(16);

  SerialUSB.print("Starting...\n");
  
  // pixy.init();

  // if (!SD.begin(chipSelect)) {
  //   SerialUSB.println("Card failed, or not present");
  //   // while (1){
  //   //   SerialUSB.println("Card failed, or not present");
  //   // }
  // }
 
  // SerialUSB.println("card initialized.");

  radio.begin();
}

void loop() {
  // declare variables for temperature (T) and pressure (P) readings
  double T, P;

  // start measurement, wait for result and save results in T and P variables 
  bmp.measureTemperatureAndPressure(T, P);
  
  // since we use it solely as pressure sensor print only "Pressure = " text
  SerialUSB.print("Pressure = ");
  // print also value of pressure with two decimal places
  SerialUSB.print(P, 2);
  // print units - in this case the library returns hPa
  SerialUSB.println(" hPa");

  SerialUSB.print("Temperature = ");
  // print also value of pressure with two decimal places
  SerialUSB.print(T, 2);
  // print units - in this case the library returns hPa
  SerialUSB.println(" C");
  int i; 
  // grab blocks!
  // pixy.ccc.getBlocks();
  // SerialUSB.print("Detected");
  // SerialUSB.print(";");
  // SerialUSB.print(pixy.ccc.numBlocks);
  // //If there are detect blocks, print them!
  // if (pixy.ccc.numBlocks)
  // {
  //   File dataFile = SD.open("gowno.csv", FILE_WRITE);
  //   if (dataFile) {
  //     SerialUSB.print("Detected");
  //     SerialUSB.print(";");
  //     SerialUSB.print(pixy.ccc.numBlocks);
  //     dataFile.print("Detected");
  //     dataFile.print(";");
  //     dataFile.print(pixy.ccc.numBlocks);
      
  //     for (i=0; i<pixy.ccc.numBlocks; i++)
  //     {
  //       SerialUSB.print(";");
  //       SerialUSB.print("block;");
  //       SerialUSB.print(i);
  //       pixy.ccc.blocks[i].print();
  //       dataFile.print(";");
  //       dataFile.print("block;");
  //       dataFile.print(i);
  //       pixy.ccc.blocks[i].print();
  //         if(i>pixy.ccc.numBlocks){
  //           break;
  //         }
  //     }
  //     dataFile.println();
  //     dataFile.close();
  //     SerialUSB.println();
  //   }

  //   else {
  //     SerialUSB.println("error opening gowno.csv");
  //   }
  // }
  frame.print(T);
  frame.print(";");
  frame.print(P);
  frame.print("");

  radio.transmit(frame);

  // print frame also on SerialUSB
  SerialUSB.println(frame);

  // clear frame to make it ready for new data
  frame.clear();
  delay(2000);
}
