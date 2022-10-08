// Sensor.h
#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

class Sensor {
  private:
    int ledPin;
    unsigned char ledState;



  public:
    Sensor(int pin);
    void turnON();
    void turnOFF();
    int getState();
};

#endif
