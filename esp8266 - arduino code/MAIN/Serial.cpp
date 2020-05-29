#include "velomoteur.h"
#include <Arduino.h>

#if USE_SERIAL_DISPLAY

void InitSerial(){
  Serial.begin(9600);
  Serial.println();
  Serial.println("setup");  
}


void DisplaySerial(TValuesUtiles unValuesUtiles){
   Serial.println();
   Serial.println();
   Serial.println();
   Serial.println("______________________________________________________________________________________________________________________________________________________________________________________________________________________");
   Serial.println("Vitesse instantanee :" + String(unValuesUtiles.m_iSpeed) + "km/h");
   Serial.println("Vitasse moyene :     " + String(unValuesUtiles.m_fSpeedMoy,1) + "km/h");
   Serial.println("Courant instantane : " + String(unValuesUtiles.m_fIntensitee,1) +"A");
   Serial.println("Courant moyen :      " + String(unValuesUtiles.m_fIntensiteeMoy,1) + "A");
   Serial.println("Autonomie :          " + String(unValuesUtiles.m_fAutonomie,1) + "km");
   Serial.println("Distance parcourue : " + String(unValuesUtiles.m_fDistanceFaite,1) + "km");
   Serial.println("Batterie :           " + String(unValuesUtiles.m_fCapactee,1) + "%");
   Serial.println("______________________________________________________________________________________________________________________________________________________________________________________________________________________");
}
#endif
