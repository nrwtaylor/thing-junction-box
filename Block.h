// Sensor.h
#ifndef Block_h
#define Block_h

#include <Arduino.h>

class Block {
  private:
    int ledPin;
    unsigned char ledState;

  public:
    Block(int pin, int signals, int sensors);
    void turnON();
    void turnOFF();
    int getState();
};

#endif
