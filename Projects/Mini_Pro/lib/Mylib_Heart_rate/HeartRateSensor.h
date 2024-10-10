#ifndef HEARTRATESENSOR_H
#define HEARTRATESENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

class HeartRateSensor {
public:
    HeartRateSensor();
    void begin();
    void update();
    int getAverageBPM();
    bool getisnofigure();
    MAX30105 particleSensor;

private:
    void configulation();
    void calculator_Haert_Rate();

    static const byte RATE_SIZE = 4;
    byte rates[RATE_SIZE];
    byte rateSpot;
    long lastBeat;
    float beatsPerMinute;
    int beatAvg;
    const int ledPin = D4;
    int isnofigure ;
};

#endif
