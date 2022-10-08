// Block.cpp
#include "Block.h"
#include "Sensor.h"
#include "Signal.h"

Block::Block(int pin, int sensors, int signals) {

  Sensor sensor1(2); // create a LED object that attach to pin 2
  Sensor sensor2(3); // create a LED object that attach to pin 3

//  Serial.print(sensors); // this can detect.
//  Serial.println();
  ledPin   = pin;
  ledState = LOW;
  pinMode(ledPin, OUTPUT);
}

void Block::turnON() {
//    Serial.print(sensors); // this can detect.
//  Serial.println();
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
}

void Block::turnOFF() {
  ledState = LOW;
  digitalWrite(ledPin, ledState);
}

int Block::getState() {
  return ledState;
}
