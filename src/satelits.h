#ifndef __SATELITS_H__
#define __SATELITS_H__
#include <Arduino.h>

class satelit {
  private:
    uint8_t timeout;
  public:
    void start_timeout();
    void reset_timeout();
    //~satelit();
};

class sensor : satelit {
  public:
    String voltage = " NAN";
    String degree = " NAN";
    String humidity = " NAN";
};

class actor : satelit {
  public:
    bool gn = true;
    int from = 0;
    int number = 0;
    String nam;
};

#endif