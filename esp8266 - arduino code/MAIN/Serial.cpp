#include "velomoteur.h"
#include <Arduino.h>

#if USE_SERIAL_DISPLAY
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void InitSerial(){
  mySerial.begin(9600);
  mySerial.println();
  mySerial.println("setup");  
}
void DisplaySerialInterrupt(){
  mySerial.println();
  mySerial.println("Interrupt");
  mySerial.println();
}

void DisplaySerial(TValuesUtiles unValuesUtiles){
   mySerial.println();
   mySerial.println();
   mySerial.println();
   mySerial.println("______________________________________________________________________________________________________________________________________________________________________________________________________________________");
   mySerial.println("Vitesse instantanee :" + String(unValuesUtiles.m_iSpeed) + "km/h");
   mySerial.println("Vitasse moyene :     " + String(unValuesUtiles.m_fSpeedMoy,1) + "km/h");
   mySerial.println("Courant instantane : " + String(unValuesUtiles.m_fIntensitee,1) +"A");
   mySerial.println("Courant moyen :      " + String(unValuesUtiles.m_fIntensiteeMoy,1) + "A");
   mySerial.println("Autonomie :          " + String(unValuesUtiles.m_fAutonomie,1) + "km");
   mySerial.println("Distance parcourue : " + String(unValuesUtiles.m_fDistanceFaite,1) + "km");
   mySerial.println("Batterie :           " + String(unValuesUtiles.m_fCapactee,1) + "%");
   mySerial.println("______________________________________________________________________________________________________________________________________________________________________________________________________________________");
}
#endif
