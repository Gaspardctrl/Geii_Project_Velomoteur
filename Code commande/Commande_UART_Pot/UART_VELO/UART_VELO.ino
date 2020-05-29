#include "VescUart.h"

VescUart VESCUART;

const byte Bp1 = 3;
const uint8_t PotentiometerPin = A0;
uint16_t Speed = 0;
bool Etat_Bp = 0;

uint32_t LastTime = 0; 

void setup() {

  Serial.begin(115200);
  VESCUART.setSerialPort(&Serial);

    // Interrupts
  attachInterrupt(digitalPinToInterrupt(Bp1), Interrupt_Bp, CHANGE);

}

void loop() {
  if (Etat_Bp==1)
  {
    if((millis() - LastTime) > 10)
    {

      VESCUART.setRPM(map(analogRead(PotentiometerPin), 0, 1023, 5000, 11000));
    
      LastTime = millis();
    } 
  }
 }


 void  Interrupt_Bp (void)
 {
  if(Etat_Bp==0)
  {
    Etat_Bp = 1;
  }
  else 
  {
    Etat_Bp = 0;
  }
}
