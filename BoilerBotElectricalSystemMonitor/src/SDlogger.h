#ifndef SDLOGGER_H
#define SDLOGGER_H
// Header file for SD logger

#include <SPI.h>
#include <SD.h>
#include <stdint.h>
#include <Arduino.h>

class SDloggerFactory
{
private:
    File fp;
public:
    SDloggerFactory();
    bool init(uint8_t);
    size_t logByte(byte*, size_t);
    size_t logText(char*);
    void info(Print*);
    bool setFp(char*, const char* = FILE_WRITE);
    File getFp();
};

#endif