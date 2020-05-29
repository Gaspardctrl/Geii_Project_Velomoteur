#include "velomoteur.h"
#include <Arduino.h>
unsigned long mlilistime;

void Calcul(TValuesUtiles &unValuesUtiles,TValuesDebug &unValuesDebug){
  mlilistime = millis();
  unValuesDebug.m_iEchantillons = unValuesDebug.m_iEchantillons +1;
  unValuesDebug.m_iTotalSpeed += unValuesUtiles.m_iSpeed;
  unValuesUtiles.m_fSpeedMoy = (float)unValuesDebug.m_iTotalSpeed / unValuesDebug.m_iEchantillons;
  unValuesDebug.m_fTotalIntensitee = unValuesDebug.m_fTotalIntensitee + unValuesUtiles.m_fIntensitee;
  unValuesUtiles.m_fIntensiteeMoy = unValuesDebug.m_fTotalIntensitee / (float)unValuesDebug.m_iEchantillons;
  unValuesUtiles.m_fDistanceFaite = unValuesUtiles.m_fSpeedMoy * (mlilistime / 3600000.00);
  unValuesUtiles.m_fAutonomie = unValuesUtiles.m_fSpeedMoy * (CAPACITEE_BAT_EN_Ah/unValuesUtiles.m_fIntensiteeMoy)*(unValuesUtiles.m_fCapactee/100.0);
}

void InitVar(TValuesUtiles &unV, TValuesDebug &unVd){
  unV.m_iSpeed = 0;
  unV.m_fSpeedMoy = 0;
  unV.m_fIntensitee = 0;
  unV.m_fIntensiteeMoy = 0;
  unV.m_fAutonomie = 0;
  unV.m_fDistanceFaite = 0;
  unV.m_fCapactee = 0;
  unVd.m_iTotalSpeed = 0;
  unVd.m_fTotalIntensitee = 0;
  unVd.m_iEchantillons = 0;
}

void InitSimulate(TValuesUtiles &unV, TValuesDebug &unVd){
  unV.m_iSpeed = 50;
  unV.m_fSpeedMoy = 0;
  unV.m_fIntensitee = 100;
  unV.m_fIntensiteeMoy = 0;
  unV.m_fAutonomie = 0;
  unV.m_fDistanceFaite = 0;
  unV.m_fCapactee = 100;
  unVd.m_iTotalSpeed = 0;
  unVd.m_fTotalIntensitee = 0;
  unVd.m_iEchantillons = 0;
}

void Simulate(TValuesUtiles &unV, TValuesDebug &unVd){
  if(unVd.m_iEchantillons <= 50){
    mlilistime = millis();
    unV.m_fIntensitee =  unV.m_fIntensitee - 1;
    unV.m_iSpeed = unV.m_iSpeed-1;
    unV.m_fCapactee = 100 - (unV.m_fIntensiteeMoy * (mlilistime / 3600000.0)/CAPACITEE_BAT_EN_Ah)*100;
  }
}
