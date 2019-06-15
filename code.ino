#include "SevSeg.h" 
SevSeg sevseg;

void setup() { 
  byte numDigits= 4; 
  byte digitPins[] = {2, 3, 4, 5}; 
  byte segmentPins[] = {8, 9, 10, 11, 12, 13, 14, 15}; 
  sevseg.begin(COMMON_CATHODE , numDigits, digitPins, segmentPins);
  pinMode(6,INPUT);   
  pinMode(17,INPUT); 
}
int Hour = 0;
int Min = 0;
unsigned long previousTime = 0;
unsigned long interval = 300;
void loop() {
  unsigned long currentTime  = millis();
  
  if(digitalRead(6) == HIGH) 
    Min = Hour = 0; 
  
  if(currentTime-previousTime > interval) {  
    previousTime = currentTime ;  
 
    if(digitalRead(17) == LOW){
      Min = Min + 1; 
      if (Min == 60) { 
        Min = 0; 
        if (Hour == 23) 
          Hour=0; 
        else 
          Hour++; 
      } 
    }
    else {
      if(Min == 0 && Hour == 0) {
        Min = 59;
        Hour = 23;
      }
      else {
        Min = Min - 1; 
        if (Min == -1) { 
          Min = 59; 
          if (Hour == -1) 
            Hour=23; 
          else 
            Hour--; 
        } 
      }
    }
  }
  sevseg.setNumber(Hour * 100 + Min, 4); 
  sevseg.refreshDisplay();
}
