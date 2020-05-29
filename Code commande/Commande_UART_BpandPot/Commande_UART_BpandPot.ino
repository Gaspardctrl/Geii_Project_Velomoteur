  
#include "VescUart.h"

#define VITESSE_MAX       11000
#define VITESSE_MIN       5000


VescUart VESCUART;

const byte Bp1 = 3;
const uint8_t PotentiometerPin = A0;
uint16_t Speed = 0;
bool Etat_Bp = false;

uint32_t LastTime = 0; 

void setup() {

  Serial.begin(115200);
  VESCUART.setSerialPort(&Serial);

    // Interrupts
  attachInterrupt(digitalPinToInterrupt(Bp1), Interrupt_Bp, CHANGE);

}

void loop() {
  if (Etat_Bp==true)
  {
    if((millis() - LastTime) > 10)
    {

      VESCUART.setRPM(map(analogRead(PotentiometerPin), 0, 1023, VITESSE_MIN, VITESSE_MAX));
    
      LastTime = millis();
    } 
  }
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
