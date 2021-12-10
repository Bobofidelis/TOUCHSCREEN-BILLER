#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

const char *msg ;
RH_ASK driver;


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
//const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;


const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define LCD_RESET A4
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30

int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY   tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
#define BLACK   0x0000

#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30


void drawHome()
{
  tft.fillScreen(WHITE);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);     //Page border
  tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);  //Dish1
  tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);  //Dish2
  tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //Dish3
  tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);
  tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
  tft.drawRoundRect(10, 190, 190, 40, 8, WHITE); //Call Waiter
  tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);  //Dish4
  tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 90, 100, 40, 8, WHITE); //Dish5
  tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 140, 100, 40, 8, WHITE); //Dish6
  tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
  tft.drawRoundRect(210, 190, 100, 40, 8, WHITE); //Bill
  tft.setCursor(60, 0);
  tft.setTextSize(3);
  tft.setTextColor(LIME);
  tft.print("   Menu");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(37, 47);
  tft.print(" Dish1");
  tft.setCursor(37, 97);
  tft.print(" Dish2");
  tft.setCursor(37, 147);
  tft.print(" Dish3");
  tft.setCursor(23, 197);
  tft.print(" Call Waiter");
  tft.setCursor(187, 47);
  tft.print(" Dish4");
  tft.setCursor(187, 97);
  tft.print(" Dish5");
  tft.setCursor(187, 147);
  tft.print(" Dish6");
  tft.setCursor(227, 197);
  tft.print(" Bill");
  //  delay(500);
}
int oldcolor, currentcolor, currentpcolour;
#define MINPRESSURE 20
#define MAXPRESSURE 1000
void setup() {
  // put your setup code here, to run once:
    // Reading TFT ID:
  uint16_t ID=tft.readID();
Serial.begin(9600);
Serial.println(ID); 
//Initializing TFT display:
tft.begin(ID);
tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(50, 140);
  tft.print("Loading...");
  tft.setTextColor(tft.color565(255, 255, 0));
  tft.setCursor(30, 70);
  tft.print("By:");
  tft.setCursor(10, 100);
  tft.print("fidelis");
  delay(2000);
  for (int i; i < 250; i++)
  {
    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, RED);
    delay(0.000000000000000000000000000000000000000000000000001);
  }
  tft.fillScreen(BLACK);
  
  if (!driver.init())
      Serial.println("init failed");
      
  drawHome();
  pinMode(13, OUTPUT);
}
void transmit()
{  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(1000);
  }
void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(13, HIGH);
  uint16_t xpos, ypos;  //screen coordinates
  tp = ts.getPoint();
 
  digitalWrite(13, LOW);
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
    {
      xpos = map(tp.y, TS_BOT, TS_TOP, 0, 320);
      ypos = map(tp.x, TS_LEFT, TS_RT, 0, 240);      
      if (xpos > 180 && xpos < 280 && ypos > 190 && ypos < 230)
      {
        Serial.println("Dish1");
        msg = "Dish1 Ordered";
        transmit();
        tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
        tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);
        tft.setCursor(37, 47);
        tft.println(" Dish1");
        delay(70);
        }
      if (xpos > 180 && xpos < 280 && ypos > 140 && ypos < 180)
      {
        Serial.println("Dish2");
        msg = "Dish2 Ordered";
        transmit();
        tft.fillRoundRect(30, 90, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
        tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);
        tft.setCursor(37, 97);
        tft.println(" Dish2");
        delay(70);      
      }
      if (xpos > 180 && xpos < 280 && ypos > 90 && ypos < 130)
      {
        Serial.println("Dish3");
        msg = "Dish3 Ordered";
        transmit();
        tft.fillRoundRect(30, 140, 100, 40, 8, WHITE);   //rgb led
        delay(70);
        tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //rgb led
        tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);   //rgb led
        tft.setCursor(37, 147);
        tft.print(" Dish3");
        delay(70);       
      }
      if (xpos > 210 && xpos < 310 && ypos > 40 && ypos < 80)
      {
        Serial.println("Call Waiter");
        msg = "CallingWaiter";
        transmit();
        tft.fillRoundRect(10, 190, 190, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
        tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);
        tft.setCursor(23, 197);
        tft.print(" Call Waiter");
        delay(70);
      }
      if (xpos > 30 && xpos < 130 && ypos > 190 && ypos < 230)
      {
        Serial.println("Dish4");
        msg = "Dish4 Ordered";
        transmit();
        tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
        tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);
        tft.setCursor(187, 47);
        tft.print(" Dish4");
        delay(70);
      }
      if (xpos > 30 && xpos < 130 && ypos > 140 && ypos < 180 )
      {
        Serial.println("Dish5");
        msg = "Dish5 Ordered";
        transmit();
        tft.fillRoundRect(180, 90, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
        tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);
        tft.setCursor(187, 97);
        tft.print(" Dish5");
        delay(70);
      }
      if (xpos > 30 && xpos < 130 && ypos > 90 && ypos < 130)
      {
        Serial.println("Dish6");
        msg = "Dish6 Ordered";
        transmit();
        tft.fillRoundRect(180, 140, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
        tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);
        tft.setCursor(187, 147);
        tft.print(" Dish6");
        delay(70);
      }

      if (xpos > 10 && xpos < 210 && ypos > 40 && ypos < 80)
      {
        Serial.println("Bill");
        msg = "Customer Bill";
        transmit();
        tft.fillRoundRect(210, 190, 100, 40, 8, WHITE);
        delay(70);
        tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
        tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);
        tft.setCursor(227, 197);
        tft.print(" Bill");
        delay(70);
      }
    }
}
