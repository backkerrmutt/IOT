#include "HeartRateSensor.h"

HeartRateSensor::HeartRateSensor() : rateSpot(0), lastBeat(0), beatsPerMinute(0), beatAvg(0) {}

void HeartRateSensor::begin() {
    Wire.setClock(400000); // Set I2C speed to 400kHz
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT); // Set LED pin as output
    digitalWrite(ledPin, LOW);

    // Initialize sensor
    particleSensor.begin(Wire, I2C_SPEED_FAST); // Use default I2C port, 400kHz speed
    particleSensor.setup();                     // Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A);  // Turn Red LED to low to indicate sensor is running
}

void HeartRateSensor::update() {
    calculateHeartRate();
}

int HeartRateSensor::getHeartRate() {
    return beatAvg;
}

float HeartRateSensor::getSpO2() {
    long irValue = particleSensor.getIR();
    long redValue = particleSensor.getRed();
    float ratio = (float)redValue / irValue;
    return 110 - 25 * ratio;  // Simplified formula for SpO2 calculation
}

void HeartRateSensor::calculateHeartRate() {
    long irValue = particleSensor.getIR(); // Reading the IR value it will permit us to know if there's a finger on the sensor or not

    if (irValue > 50000) {
        if (checkForBeat(irValue) == true) { // If a heart beat is detected, call checkForBeat as frequent as possible to get accurate value
            long delta = millis() - lastBeat; // Measure duration between two beats
            lastBeat = millis();
            beatsPerMinute = 60 / (delta / 1000.0);          // Calculating the BPM
            if (beatsPerMinute < 255 && beatsPerMinute > 20) { // To calculate the average we store some values (4) then do some math to calculate the average
                rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
                rateSpot %= RATE_SIZE;                    // Wrap variable

                // Take average of readings
                beatAvg = 0;
                for (byte x = 0; x < RATE_SIZE; x++)
                    beatAvg += rates[x];
                beatAvg /= RATE_SIZE;

                // Blink LED
                digitalWrite(ledPin, HIGH); // Turn the LED on
                delay(100);                 // Wait for 100 milliseconds
                digitalWrite(ledPin, LOW);  // Turn the LED off

                Serial.print("BPM: ");
                Serial.println(beatAvg);
            }
        }
    } else {
        Serial.println("Place your finger in sensor and wait..");
    }
}
