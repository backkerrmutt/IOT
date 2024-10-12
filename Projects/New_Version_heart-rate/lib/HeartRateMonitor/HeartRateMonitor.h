#ifndef HEART_RATE_MONITOR_H
#define HEART_RATE_MONITOR_H

#include <Arduino.h>
#include <MAX30105.h>
#include <LiquidCrystal_I2C.h>
#include <heartRate.h>
#include <Wire.h>

class HeartRateMonitor {
public:
    HeartRateMonitor();
    void Init();
    void Update();
    float calculateBeatAvg();
    bool HeartRate_Display(float val);
    bool My_Delay(unsigned long interval);
    LiquidCrystal_I2C lcd;

private:
    MAX30105 particleSensor;
    #define RATE_SIZE 4
    byte rates[RATE_SIZE];
    byte rateSpot;
    long lastBeat;
    float beatsPerMinute;
    int beatAvg;
    unsigned long previousMillis;
    int previousValue;
    int LED_DISPLAY;
};

#endif
