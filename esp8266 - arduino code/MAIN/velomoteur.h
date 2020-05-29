#define Black 0x0000
#define White 0xFFFF
//________________________________
#define USE_EINK_DISPLAY false
#define USE_SERIAL_DISPLAY true
#define USE_SIMULATE_Vesc true
#define D_ROUE_EN_CM 25 //FAUX
#define RAPPORT_REDUCTION 1  ///FAUX
#define CAPACITEE_BAT_EN_Ah 17 ///FAUX
//________________________________

#if USE_EINK_DISPLAY
  #include <GxEPD2_BW.h>
  #include <GxEPD2_3C.h>
  #include <Fonts/FreeMonoBold9pt7b.h>
  #include <U8g2_for_Adafruit_GFX.h>
  #if defined (ESP8266)
    #define ENABLE_GxEPD2_GFX 0
  #endif
  extern const unsigned char myBitmapBitmap [];
#endif

#if !USE_SIMULATE_Vesc
  #include <VescUart.h>  
  extern VescUart UART;
#endif

typedef struct
{
  int m_iSpeed;
  float m_fSpeedMoy;
  float m_fIntensitee;
  float m_fIntensiteeMoy;
  float m_fAutonomie;
  float m_fDistanceFaite;
  float m_fCapactee;
}TValuesUtiles;

typedef struct
{
  long int m_iTotalSpeed;
  float m_fTotalIntensitee;
  long int m_iEchantillons;
}TValuesDebug;

void Calcul(TValuesUtiles &unValuesUtiles,TValuesDebug &unValuesDebug);
#if USE_EINK_DISPLAY
void InitEInk();
void ReupdateEink();
void DisplayEink(TValuesUtiles unValuesUtiles,TValuesUtiles unOldValuesUtiles);
void Lock();
void Clear();
#endif
#if USE_SERIAL_DISPLAY
void InitSerial();
void DisplaySerial(TValuesUtiles unValuesUtiles);
#endif
void InitVar(TValuesUtiles &unV, TValuesDebug &unVd);
#if !USE_SIMULATE_Vesc
void VescGetData(TValuesUtiles &unV, TValuesDebug &unVd);
void VescSetup();
void SetRPM(float rpm);
#endif
#if USE_SIMULATE_Vesc
void Simulate(TValuesUtiles &unV, TValuesDebug &unVd);
void InitSimulate(TValuesUtiles &unV, TValuesDebug &unVd);
#endif
