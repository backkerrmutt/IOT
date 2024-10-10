#include "HeartRateSensor.h"
int count;
HeartRateSensor::HeartRateSensor() : rateSpot(0), lastBeat(0), beatsPerMinute(0), beatAvg(0)
{
    for (byte i = 0; i < RATE_SIZE; i++)
    {
        rates[i] = 0;
    }
}

void HeartRateSensor::begin()
{
    configulation();
}

void HeartRateSensor::update()
{
    calculator_Haert_Rate();   
}

int HeartRateSensor::getAverageBPM()
{
    return beatAvg;
}

bool HeartRateSensor::getisnofigure()
{
    return isnofigure;
}

void HeartRateSensor::configulation()
{
    Wire.setClock(400000);
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    particleSensor.begin(Wire, I2C_SPEED_FAST);
    particleSensor.setup();
    // particleSensor.setPulseAmplitudeRed(0x0A);
}

void HeartRateSensor::calculator_Haert_Rate()
{
    long irValue = particleSensor.getIR();

    if (irValue > 50000)
    {
        if (checkForBeat(irValue) == true)
        {
            long delta = millis() - lastBeat;
            lastBeat = millis();
            beatsPerMinute = 60 / (delta / 1000.0);
            if (beatsPerMinute < 255 && beatsPerMinute > 20)
            {
                rates[rateSpot++] = (byte)beatsPerMinute;
                rateSpot %= RATE_SIZE;

                beatAvg = 0;
                for (byte x = 0; x < RATE_SIZE; x++)
                    beatAvg += rates[x];
                beatAvg /= RATE_SIZE;

                digitalWrite(ledPin, HIGH);
                delay(100);
                digitalWrite(ledPin, LOW);
            }
        }
        isnofigure = false;
    }
    else
    {
        isnofigure = true;
    }
}
