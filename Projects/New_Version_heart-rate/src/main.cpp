#include <Arduino.h>
#include <HeartRateMonitor.h>

HeartRateMonitor hrm; // สร้าง object จาก library HeartRateMonitor

// Machine_Stats Values
const unsigned int IDLE = 0 ; // state รอก่อนเลือกโหมด
const unsigned int CHILD = 1; // state เด็ก
const unsigned int MIDDLE_AGW = 2; // state วัยกลางคน
unsigned int state ; // ค่าเปลี่ยน state

void setup()
{
  // state = IDLE; 
  hrm.Init();
}
void loop()
{
  // if (state == IDLE)
  // {
  //   // อ่านค่าจาก button ถ้าเลือก btn_1 ไปโหมดเด็ก แต้ถ้าเลือก btn_2 ไปโหมดวัยกลางคน
  //   return ;
    
  // }
  
  float heartrate = hrm.calculateBeatAvg();
  if (heartrate == 0)
  {
    if (hrm.My_Delay(1000))
    {
      hrm.lcd.clear();
      hrm.lcd.print("No Figure!!!");
    }
  }
  else
  {
    if (hrm.HeartRate_Display(heartrate))
    {
      hrm.lcd.clear();
      hrm.lcd.print(heartrate, 0);
    }
  }
}
