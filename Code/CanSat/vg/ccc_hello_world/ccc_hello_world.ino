#include <SPI.h>
#include <Pixy2.h>
#include <SD.h>

Pixy2 pixy;
const int chipSelect = 11;

void setup()
{
  Serial.begin(115200);
  SerialUSB.print("Starting...\n");
  
  pixy.init();
  if (!SD.begin(chipSelect)) {
    SerialUSB.println("Card failed, or not present");
    while (1);
  }
 
  SerialUSB.println("card initialized.");
}

void loop()
{ 
  int i; 
  // grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    File dataFile = SD.open("gowno.csv", FILE_WRITE);
    if (dataFile) {
      SerialUSB.print("Detected");
      SerialUSB.print(";");
      SerialUSB.print(pixy.ccc.numBlocks);
      dataFile.print("Detected");
      dataFile.print(";");
      dataFile.print(pixy.ccc.numBlocks);
      
      for (i=0; i<pixy.ccc.numBlocks; i++)
      {
        SerialUSB.print(";");
        SerialUSB.print("block;");
        SerialUSB.print(i);
        pixy.ccc.blocks[i].print();
        dataFile.print(";");
        dataFile.print("block;");
        dataFile.print(i);
        pixy.ccc.blocks[i].print();
      }
      dataFile.close();
      SerialUSB.println();
    }

    else {
      SerialUSB.println("error opening gowno.csv");
    }
  }
  delay(2000);
}