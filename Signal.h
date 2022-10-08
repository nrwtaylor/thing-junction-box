// Signal.h
#ifndef Signal_h
#define Signal_h

#include <Arduino.h>

class Signal {
  private:
    int ledPin;
    unsigned char ledState;



  public:
    Signal(int pin);
    void turnON();
    void turnOFF();
    int getState();
};

#endif
