#include <SPI.h>
#include <SD.h>
#include "SDlogger.h"

// Set the pins used
#define cardSelect 33

// Define data structure
struct DataPacket
{
  unsigned long timestamp;
  float vbatt;
  float vcap;
  float ibatt;
  float tempC;
  bool ableBoost;
  float vertiDist;
  float leftDist;
  float rightDist;
  float rearDist;
  float leftGrabDist;
  float rightGrabDist;
  bool isLeftClaw;
  bool isRightClaw;
};

union SerializedDataPacket
{
  struct DataPacket rawData;
  byte serialized[50];
};

const struct DataPacket DefaultValue = {
  0, 0, 0, 1, 3, true, 0, 0, 0, 0, 0, 0, false, false
};

struct DataPacket currentMeasurement = DefaultValue;

// File logfile;
SDloggerFactory SDlogger = SDloggerFactory();

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) { 
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

// This line is not needed if you have Adafruit SAMD board package 1.6.2+
//   #define Serial SerialUSB

void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("SD logger test");
  SDlogger.init(cardSelect);
  SDlogger.info(&Serial);
  SDlogger.setFp("/test.txt", FILE_WRITE);
  File logfile = SDlogger.getFp();
  if( ! logfile ) {
    Serial.print("Couldnt create"); 
    Serial.println();
  }
  SerializedDataPacket packet;
  packet.rawData = currentMeasurement;
  Serial.println(SDlogger.logByte(packet.serialized, sizeof(packet)));
  SD.mkdir("/Test/");
  logfile.close();
  Serial.println("Success");

  // pinMode(13, OUTPUT);


  // // see if the card is present and can be initialized:
  // if (!SD.begin(cardSelect)) {
  //   Serial.println("Card init. failed!");
  //   error(2);
  // }
  // char filename[15];
  // strcpy(filename, "/ANALOG00.TXT");
  // for (uint8_t i = 0; i < 100; i++) {
  //   filename[7] = '0' + i/10;
  //   filename[8] = '0' + i%10;
  //   // create if does not exist, do not open existing, write, sync after write
  //   if (! SD.exists(filename)) {
  //     break;
  //   }
  // }

  // logfile = SD.open(filename, FILE_WRITE);
  // if( ! logfile ) {
  //   Serial.print("Couldnt create "); 
  //   Serial.println(filename);
  //   error(3);
  // }
  // Serial.print("Writing to "); 
  // Serial.println(filename);

  // pinMode(13, OUTPUT);
  // pinMode(8, OUTPUT);
  // Serial.println("Ready!");
}

// uint8_t i=0;
void loop() {
  // digitalWrite(8, HIGH);
  // logfile.print("A0 = "); logfile.println(analogRead(0));
  // Serial.print("A0 = "); Serial.println(analogRead(0));
  // logfile.flush();
  // digitalWrite(8, LOW);
  
  // delay(100);
}