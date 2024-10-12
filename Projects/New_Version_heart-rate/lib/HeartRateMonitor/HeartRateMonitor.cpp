#include "HeartRateMonitor.h"

HeartRateMonitor::HeartRateMonitor() : lcd(0x27, 16, 2), rateSpot(0), lastBeat(0), beatsPerMinute(0), beatAvg(0), 
previousMillis(0), previousValue(0),LED_DISPLAY(2){}

void HeartRateMonitor::Init() {
    lcd.init();
    lcd.backlight();
    Serial.begin(115200);
    Serial.println("Initializing...");
    pinMode(2, OUTPUT); // LED_SHOW_HEARTBEAT

    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30105 was not found. Please check wiring/power.");
        while (1);
    }
    Serial.println("Place your index finger on the sensor with steady pressure.");
    particleSensor.setup();
}

// void HeartRateMonitor::print(auto somthings){
//     lcd.print(somthings);
// }
// void HeartRateMonitor::clear(){
//     lcd.clear();
// }

void HeartRateMonitor::Update() {
    float val = calculateBeatAvg();
    if (val == 0) {
        if (My_Delay(1000)) {
            lcd.clear();
            lcd.print(" no Figure ");
        }
    } else {
        if (HeartRate_Display(val)) {
            lcd.clear();
            lcd.print(val, 0);
        }
    }
    Serial.println("");
}

bool HeartRateMonitor::HeartRate_Display(float val) {
    if (val != previousValue) {
        previousValue = val;
        return true;
    } else {
        return false;
    }
}

bool HeartRateMonitor::My_Delay(unsigned long interval) {

     unsigned long currentMillis = millis();
    if (currentMillis < previousMillis) {
        // Reset previousMillis if currentMillis has overflowed
        previousMillis = 0;
    }
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        return true;
    } else {
        return false;
    }

    // unsigned long currentMillis = millis();
    // if (currentMillis - previousMillis >= interval) {
    //     previousMillis = currentMillis;
    //     return true;
    // } else {
    //     return false;
    // }
}

float HeartRateMonitor::calculateBeatAvg() {
    long irValue = particleSensor.getIR();
    static float beatAvg = 0;

    if (checkForBeat(irValue)) {
        long delta = millis() - lastBeat;
        lastBeat = millis();

        float beatsPerMinute = 60.0 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] = (byte)beatsPerMinute;
            rateSpot %= 4;

            beatAvg = 0;
            for (byte x = 0; x < 4; x++) {
                beatAvg += rates[x];
            }
            beatAvg /= 4;
            digitalWrite(LED_DISPLAY, true);
            delay(100);
            digitalWrite(LED_DISPLAY, false);
        }
    }

    if (irValue < 5000) {
        return 0;
    } else {
        return beatAvg;
    }
    delay(20);
}
