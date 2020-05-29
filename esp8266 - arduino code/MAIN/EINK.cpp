#include "velomoteur.h"
#if USE_EINK_DISPLAY

  #if defined (ESP8266)
    #define ENABLE_GxEPD2_GFX 0
    GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
    U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
  #endif

void InitEInk(){
  display.init();
  u8g2Fonts.begin(display); 
  display.setRotation(0);
}
void Lock(){
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(0, 0, myBitmapBitmap, 200, 200, GxEPD_BLACK);
  ReupdateEink();
}
void Clear(){
  display.fillScreen(GxEPD_WHITE);
  ReupdateEink();
}
void ReupdateEink(){
  display.display(false);
}

void DisplayEink(TValuesUtiles unValuesUtiles,TValuesUtiles unOldValuesUtiles){
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(100+40, 160);
  display.fillRect(2, 2, 196, 45, Black);
  display.fillRect(3, 3, 97, 43, White);
  display.fillRect(101, 3, 96, 43, White);
  u8g2Fonts.setFont(u8g2_font_fur11_tr);
  u8g2Fonts.print("km/h");
  display.fillRect(10, 175, 180, 20, Black);
  u8g2Fonts.setCursor(10, 30);
  u8g2Fonts.setFont(u8g2_font_open_iconic_all_2x_t );
  u8g2Fonts.print("Z");
  u8g2Fonts.setCursor(10, 68);
  u8g2Fonts.setFont(u8g2_font_open_iconic_embedded_2x_t );
  u8g2Fonts.print("F");
  u8g2Fonts.setCursor(10+22, 68);
  u8g2Fonts.setFont(u8g2_font_fur11_tr);
  u8g2Fonts.print(" "+String(unOldValuesUtiles.m_fSpeedMoy,1) + "km/h - " + String(unOldValuesUtiles.m_fIntensiteeMoy,1) +"A");
  u8g2Fonts.setCursor(10+20, 20);
  u8g2Fonts.setFont(u8g2_font_profont17_tf );
  u8g2Fonts.print(" "+String(unOldValuesUtiles.m_fCapactee,1)+"%");
  u8g2Fonts.setCursor(200-80, 30);
  u8g2Fonts.setFont(u8g2_font_open_iconic_gui_2x_t);
  u8g2Fonts.print("I");
  u8g2Fonts.setCursor(200-60, 20);
  u8g2Fonts.setFont(u8g2_font_fur11_tr);
  u8g2Fonts.print(" "+String(unOldValuesUtiles.m_fDistanceFaite,1)+"km");
  u8g2Fonts.setCursor(10+22, 40);
  u8g2Fonts.println(" "+String(unOldValuesUtiles.m_fAutonomie,1)+"km");
  u8g2Fonts.setCursor(200-58, 40);
  u8g2Fonts.println(" "+String(unOldValuesUtiles.m_fIntensitee,1)+"A");
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setCursor(100-26, 160);
  u8g2Fonts.setFontDirection(0); 
  u8g2Fonts.setForegroundColor(fg); 
  u8g2Fonts.setBackgroundColor(bg);  
  u8g2Fonts.setFont(u8g2_font_7Segments_26x42_mn);
  if(unValuesUtiles.m_iSpeed < 10){
    u8g2Fonts.print(0);
  }
  u8g2Fonts.print(String(unValuesUtiles.m_iSpeed));
  
  display.fillRect(12, 177, 176, 16, White);
  if(unValuesUtiles.m_iSpeed <= 25){
    display.fillRect(13, 178, (174*unValuesUtiles.m_iSpeed/25), 14, Black);
  }
  else
  {
    display.fillRect(13, 178, 174, 14, Black);
  }
  display.fillRect(10, 17, 15 * unValuesUtiles.m_fCapactee/100, 10, Black);
  display.display(true);
}
#endif
