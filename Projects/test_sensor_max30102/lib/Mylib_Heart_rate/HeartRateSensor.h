#ifndef HEART_RATE_SENSOR_H
#define HEART_RATE_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

class HeartRateSensor {
public:
    HeartRateSensor();
    void begin();
    void update();
    int getHeartRate();
    float getSpO2();

private:
    void calculateHeartRate();
    MAX30105 particleSensor;
    const byte RATE_SIZE = 4;
    byte rates;
    byte rateSpot;
    long lastBeat;
    float beatsPerMinute;
    int beatAvg;
    const int ledPin = D4;
};

#endif
