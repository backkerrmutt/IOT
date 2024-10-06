#include <Arduino.h>
#include "HeartRateSensor.h"

HeartRateSensor heartRateSensor;

void setup() {
    heartRateSensor.begin();
}

void loop() {
    heartRateSensor.update();
    int bpm = heartRateSensor.getAverageBPM();
    if (bpm != 0)
    {
    Serial.print("BPM : ");
    Serial.println(bpm);
    }
    
    
}
