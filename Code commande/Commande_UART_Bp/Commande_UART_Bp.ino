// include
  #include <VescUart.h>

// Initiate VescUart class 
  VescUart VESCUART;
  
// Déclaration des variables globales  
  const byte Bp1 = 3;
  const byte Bp2 = 2;
  uint16_t Speed = 0;
  uint32_t LastTime = 0; 

void setup() {

  Serial.begin(115200);

  VESCUART.setSerialPort(&Serial);

  // Interrupts
  attachInterrupt(digitalPinToInterrupt(Bp1), Interrupt_Increase, FALLING);
  attachInterrupt(digitalPinToInterrupt(Bp2), Interrupt_Decrease, FALLING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Speed != 0){
    if((millis() - LastTime) > 10){
      VESCUART.setRPM(Speed);
      LastTime = millis();
    } 
  }
 
//  delay(500);
//  Serial.println(Speed);
}

void  Interrupt_Increase (void){
  if(Speed == 0){
    Speed = 6000;
  }
  else if (Speed >= 11000) {
    Speed = 12000;
  }
  else {
    Speed = Speed + 1000;
  }
}

void  Interrupt_Decrease (void){
  if(Speed <= 4000){
    Speed = 0;
  }
  else {
    Speed = Speed - 1000;
  }
}
