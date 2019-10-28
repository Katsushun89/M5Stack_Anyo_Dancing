#include <M5Stack.h>

#define RIGHT_ARM_PIN 22
#define LEFT_ARM_PIN 21

void setup()
{
  Serial.begin(115200);
  // Power ON Stabilizing...
  delay(500);
  M5.begin();
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  pinMode(RIGHT_ARM_PIN, OUTPUT);
  digitalWrite(RIGHT_ARM_PIN, 0);

  pinMode(LEFT_ARM_PIN, OUTPUT);
  digitalWrite(LEFT_ARM_PIN, 0);

}

void loop() {
  
  if(M5.BtnA.wasPressed())
  {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("LEFT:ON");
    digitalWrite(LEFT_ARM_PIN, 1);
  }
  if(M5.BtnB.wasPressed())
  {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("BOTH:OFF");
    digitalWrite(RIGHT_ARM_PIN, 0);
    digitalWrite(LEFT_ARM_PIN, 0);
  }
  if(M5.BtnC.wasPressed())
  {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("RIGHT:ON");
    digitalWrite(RIGHT_ARM_PIN, 1);
  }
  
  delay(100);
  M5.update();
}
