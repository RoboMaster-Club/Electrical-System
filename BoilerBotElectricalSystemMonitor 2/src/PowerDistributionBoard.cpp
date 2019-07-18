#include "PowerDistributionBoard.h"

PDP::PDP(uint8_t vBattPin, uint8_t vCapPin, uint8_t iBattPin) {
  this->vBattPin = vBattPin;
  this->vCapPin = vCapPin;
  this->iBattPin = iBattPin;
  pinMode(vBattPin, INPUT);
  pinMode(vCapPin, INPUT);
  pinMode(iBattPin, INPUT);
};

float PDP::getBatteryVoltage() {
  return (float) analogRead(vBattPin) / ANALOG_RANGE * VOLTAGE_MAX;
}

float PDP::getCapacitorVoltage() {
  return (float) analogRead(vCapPin) / ANALOG_RANGE * VOLTAGE_MAX;
}

float PDP::getBatteryCurrent() {
  return (analogRead(iBattPin) - CURRENT_REF) * CURRENT_RATIO;
};

bool PDP::canBoost() {
  // Todo set a buffer range to calculate boosting time?
  return getCapacitorVoltage() >= CAPACITOR_MIN;
}