#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "LiquidCrystal_I2C.h"
MAX30105 particleSensor;
LiquidCrystal_I2C lcd(0x57,16,2);
const int numReadings = 10; // Number of readings for the moving average
float readings[numReadings]; // Array to store the readings
int readIndex = 0; // Index of the current reading
float total = 0; // Total of the readings
float average = 0; // Average of the readings

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  particleSensor.begin(Wire, I2C_SPEED_FAST);
  particleSensor.setup();
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

long getTimeBetweenBeats() {
  static long lastBeat = 0;
  long currentBeat = millis();
  long timeBetweenBeats = currentBeat - lastBeat;
  lastBeat = currentBeat;
  return timeBetweenBeats;
}

void loop() {
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true) {
    float beatsPerMinute = 60 / (getTimeBetweenBeats() / 1000.0);

    // Subtract the last reading
    total = total - readings[readIndex];
    // Add the new reading
    readings[readIndex] = beatsPerMinute;
    total = total + readings[readIndex];
    // Advance to the next position in the array
    readIndex = readIndex + 1;

    // If we're at the end of the array, wrap around to the beginning
    if (readIndex >= numReadings) {
      readIndex = 0;
    }

    // Calculate the average
    average = total / numReadings;

    Serial.print("BPM: ");
    Serial.println(average);
    
    lcd.setCursor(0,0);
    lcd.print(average);
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
