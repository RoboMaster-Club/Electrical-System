#include "VoltageRegulator.h"

VoltageRegulator::VoltageRegulator(uint8_t vBattPin, uint8_t vCapPin, uint8_t iBattPin, 
                                  float vCapMax, float vBatMax, float vBoostRef) {
  this->vBattPin = vBattPin;
  this->vCapPin = vCapPin;
  this->iBattPin = iBattPin;
  this->vBoostRef = vBoostRef;
  this->vCapMax = vCapMax;
  this->vBatMax = vBatMax;
  pinMode(vBattPin, INPUT);
  pinMode(vCapPin, INPUT);
  pinMode(iBattPin, INPUT);
};

float VoltageRegulator::getBatteryVoltage(void) {
  return analogRead(vBattPin) / 1023 * vBatMax;
}

float VoltageRegulator::getCapacitorVoltage(void) {
  return analogRead(vCapPin) / 1023 * vCapMax;
}

float VoltageRegulator::getBatteryCurrent(void) {
  return analogRead(iBattPin) / 1023;
};

bool VoltageRegulator::canBoost(void) {
  // Todo set a buffer range to calculate boosting time?
  return getCapacitorVoltage() >= vBoostRef;
}