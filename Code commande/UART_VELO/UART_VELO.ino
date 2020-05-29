#include "VescUart.h"

VescUart VESCUART;

const uint8_t PotentiometerPin = A0;

uint32_t LastTime = 0; 

void setup() {

  Serial.begin(115200);

  VESCUART.setSerialPort(&Serial);

}

void loop() {

  if((millis() - LastTime) > 10){
/*
    VESCUART.nunchuck.valueY = map(analogRead(PotentiometerPin), 0, 1023, 0, 255);

    VESCUART.setNunchuckValues();
*/

    VESCUART.setRPM(6000/*map(analogRead(PotentiometerPin), 0, 1023, 0, 12000)*/);
    
    LastTime = millis();
  }  

 }
