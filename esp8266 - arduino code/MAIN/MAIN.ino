#include "velomoteur.h"

#define VITESSE_MAX       30
#define VITESSE_MIN       0

const uint8_t PotentiometerPin = A0;
uint16_t Acceleration = 0;

uint32_t LastTime = 0; 

const bool bUseEInk = USE_EINK_DISPLAY;
const bool bUSeSerial = USE_SERIAL_DISPLAY;
TValuesUtiles ValuesUtiles;
#if USE_EINK_DISPLAY
TValuesUtiles OldValuesUtiles;
#endif
TValuesDebug ValuesDebug;

void setup() {
  
  #if USE_EINK_DISPLAY
    InitEInk();
    OldValuesUtiles = ValuesUtiles;
    Lock();
    delay(2000);
    Clear();
  #endif
  #if !USE_SIMULATE_Vesc
    InitVar(ValuesUtiles, ValuesDebug);
    VescSetup();
  #endif
  #if USE_SIMULATE_Vesc
    InitSimulate(ValuesUtiles, ValuesDebug);
  #endif
  #if USE_SERIAL_DISPLAY
    InitSerial();
  #endif
}

void loop() {
  Calcul(ValuesUtiles,ValuesDebug);
  #if USE_EINK_DISPLAY
    if(bUseEInk){
      static int iCount = 0;
      iCount++;
      DisplayEink(ValuesUtiles,OldValuesUtiles);
      if(iCount >= 100){
        ReupdateEink();
        iCount = 0;
      }
      if((iCount%5) == 0){
        OldValuesUtiles = ValuesUtiles;
      }
    }
  #endif
  #if USE_SERIAL_DISPLAY
    if(bUSeSerial){
      DisplaySerial(ValuesUtiles);
      if(!bUseEInk){
        delay(50);
      }
    }
  #endif
  #if !USE_SIMULATE_Vesc
    VescGetData(ValuesUtiles, ValuesDebug);

    if((millis() - LastTime) > 10)
    {
      Acceleration=analogRead(PotentiometerPin);
      if(Acceleration<20){
        Acceleration = 0;
      }
      else {
        Acceleration = map(Acceleration, 0, 1023, VITESSE_MIN, VITESSE_MAX);
      }
      SetCurrent(Acceleration);
      LastTime = millis();
    } 

 
  #endif
  #if USE_SIMULATE_Vesc
     Simulate(ValuesUtiles, ValuesDebug);
  #endif
}

