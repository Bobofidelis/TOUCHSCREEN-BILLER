#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>
//String msg;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RH_ASK driver;
#define buzzer 12
void setup()
{
    Serial.begin(9600);  // Debugging only
    pinMode(buzzer, OUTPUT);
    lcd.begin(16, 2);
    lcd.write(" SMART BILLER ");
    lcd.setCursor(1,1);
    lcd.write(" BY FIDELIS ");
    delay(2000);
    lcd.clear(); 
    if (!driver.init())
         Serial.println("init failed");
}
void loop()
{
    uint8_t buf[17];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("T1:");
      lcd.print((char*)buf);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);            
    }
}
