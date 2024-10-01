#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MAX30100_PulseOximeter.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;

uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(115200);
    lcd.begin();
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");  
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{ 
    pox.update();  
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
       { 
        lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print("  Oxygen/SpO2:");
        lcd.setCursor(7,1);
        lcd.print(pox.getSpO2());
        lcd.print("%  ");
        tsLastReport = millis();
       
    }
}