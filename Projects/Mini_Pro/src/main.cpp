#include <Arduino.h>
#include "HeartRateSensor.h"
#include <LiquidCrystal_I2C.h>

HeartRateSensor heartRateSensor;
LiquidCrystal_I2C lcd(0x27,20,4); 

const int IDEL = 0;
const int CHILDHOOD = 1;
const int MIDDILE_AGE = 2;
int state ;



void setup() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Place your finger in sensor");
    state = IDEL;
    heartRateSensor.begin();
}

void loop() {

    // if (state == IDEL)
    // {
    //     Serial.println("sdfsdf");
    // }if ()
    // {
        
    // }
    
    
    


    heartRateSensor.update();
   if (heartRateSensor.getisnofigure() == false)
   {
    int bpm = heartRateSensor.getAverageBPM();
    Serial.println(bpm);
   }else{
    Serial.println("Place your finger in sensor and wait.."); 
   }
}
