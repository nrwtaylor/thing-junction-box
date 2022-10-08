// Sensor.cpp
#include "Sensor.h"

Sensor::Sensor(int pin) {
  ledPin   = pin;
  ledState = LOW;
  pinMode(ledPin, OUTPUT);
}

void Sensor::turnON() {
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
}

void Sensor::turnOFF() {
  ledState = LOW;
  digitalWrite(ledPin, ledState);
}

int Sensor::getState() {
  return ledState;
}
