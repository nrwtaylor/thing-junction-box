
// Signal.cpp
#include "Signal.h"

Signal::Signal(int pin) {
  ledPin   = pin;
  ledState = LOW;
  pinMode(ledPin, OUTPUT);
}

void Signal::turnON() {
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
}

void Signal::turnOFF() {
  ledState = LOW;
  digitalWrite(ledPin, ledState);
}

int Signal::getState() {
  return ledState;
}
