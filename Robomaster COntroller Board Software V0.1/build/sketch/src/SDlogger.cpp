#include "SDlogger.h"

SDloggerFactory::SDloggerFactory() {

}

bool SDloggerFactory::init(uint8_t chipSelect) {
    return SD.begin(chipSelect);
}

size_t SDloggerFactory::logByte(byte* data, size_t size) {
    size_t length = fp.write(data, size);
    fp.flush();
    return length;
}

size_t SDloggerFactory::logText(char* text) {
    size_t length = fp.print(text);
    fp.flush();
    return length;
}

void SDloggerFactory::info(Print* stream) {
    stream->printf("Card Size: %lu\nTotal Bytes: %lu\nUsed Bytes: %lu\n",
    SD.cardSize(), SD.totalBytes(), SD.usedBytes());
}

bool SDloggerFactory::setFp(char* filePath, const char* mode) {
    fp = SD.open(filePath, mode);
    return true;
}

File SDloggerFactory::getFp() {
    return fp;
}