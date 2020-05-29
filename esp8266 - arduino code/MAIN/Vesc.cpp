#include "velomoteur.h"
#include <Arduino.h>
#if !USE_SIMULATE_Vesc

//https://github.com/SolidGeek/VescUart

VescUart UARTVESC;
#include <SoftwareSerial.h>
SoftwareSerial serial1(13, 15);

void VescSetup() {
  serial1.begin(19200);
  UARTVESC.setSerialPort(&serial1);
}

void VescGetData(TValuesUtiles &unV, TValuesDebug &unVd){
  if ( UARTVESC.getVescValues() ) {
    unV.m_iSpeed = UARTVESC.data.rpm * 60 * D_ROUE_EN_CM/100 * PI / RAPPORT_REDUCTION;
    unV.m_fIntensitee = UARTVESC.data.avgMotorCurrent;
    unVd.m_fTotalIntensitee =  UARTVESC.data.ampHours;
    unV.m_fCapactee = -10.945 * UARTVESC.data.inpVoltage + 115.13;
//    if(UARTVESC.data.inpVoltage <= 45.5) {
//        unV.m_fCapactee = 0;
//    } else if(UARTVESC.data.inpVoltage <= 46.04) {
//        unV.m_fCapactee = 10;
//    } else if(UARTVESC.data.inpVoltage <= 46.64) {
//        unV.m_fCapactee = 20;
//    } else if(UARTVESC.data.inpVoltage <= 47.24) {
//        unV.m_fCapactee = 30;
//    } else if(UARTVESC.data.inpVoltage <= 47.84) {
//        unV.m_fCapactee = 40;
//    } else if(UARTVESC.data.inpVoltage <= 48.40) {
//        unV.m_fCapactee = 50;
//    } else if(UARTVESC.data.inpVoltage <= 48.96) {
//        unV.m_fCapactee = 60;
//    } else if(UARTVESC.data.inpVoltage <= 49.48) {
//        unV.m_fCapactee = 70;
//    } else if(UARTVESC.data.inpVoltage <= 50) {
//        unV.m_fCapactee = 80;
//    } else if(UARTVESC.data.inpVoltage <= 50.48) {
//        unV.m_fCapactee = 90;
//    } else if(UARTVESC.data.inpVoltage <= 50.92) {
//        unV.m_fCapactee = 100;
//    } else if(UARTVESC.data.inpVoltage >= 50.92) {
//        unV.m_fCapactee = 100;
//    }
  }
}

void SetRPM(float rpm){
  UARTVESC.setRPM(rpm);
  //BESOIN D4AJOUTER VERIF DE MAX ET MIN
}
#endif
