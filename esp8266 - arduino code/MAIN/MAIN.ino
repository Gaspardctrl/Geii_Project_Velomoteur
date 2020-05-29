#include "velomoteur.h"

#define VITESSE_MAX       11000
#define VITESSE_MIN       5000

const byte Bp1 = 3;
const uint8_t PotentiometerPin = A0;
uint16_t Speed = 0;
bool Etat_Bp = false;

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
    attachInterrupt(digitalPinToInterrupt(Bp1), Interrupt_Bp, CHANGE);
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
     if (Etat_Bp==true)
  {
    if((millis() - LastTime) > 10)
    {

      SetRPM(map(analogRead(PotentiometerPin), 0, 1023, VITESSE_MIN, VITESSE_MAX));
    
      LastTime = millis();
    } 
  }
 
  #endif
  #if USE_SIMULATE_Vesc
     Simulate(ValuesUtiles, ValuesDebug);
  #endif
}


void  Interrupt_Bp (void)
 {
  if(Etat_Bp==false)
  {
    Etat_Bp = 1;
  }
  else 
  {
    Etat_Bp = 0;
  }
}
