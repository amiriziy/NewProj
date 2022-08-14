
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/TomThumb.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include <Fonts/FreeMonoOblique12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>

#include <Fonts/nexa_black15pt7b.h>
#include <string.h>
#include <stdio.h>

#define TFT_CS 5
#define TFT_RST 22 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 21
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//
String jdate;   // Jalali Date String
int JY, JM, JD; // Jalali Year & Month & Day Intiger

// color definitions
const uint16_t Display_Color_Black = 0x0000;
const uint16_t Display_Color_Blue = 0x001F;
const uint16_t Display_Color_Red = 0xF800;
const uint16_t Display_Color_Green = 0x07E0;
const uint16_t Display_Color_Cyan = 0x07FF;
const uint16_t Display_Color_Magenta = 0xF81F;
const uint16_t Display_Color_Yellow = 0xFFE0;
const uint16_t Display_Color_White = 0xFFFF;
const uint16_t Display_Color_Whitew = 0xDFDF;
const uint16_t Display_Color_LightCyan = 0xBFBF;
const uint16_t Display_Color_DarkCyan = 0x1111;

// The colors we actually want to use
uint16_t Display_Text_Color = Display_Color_Green;
uint16_t Display_Backround_Color = Display_Color_White;

// assume the display is off until configured in setup()
bool isDisplayVisible = false;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t MaxString = 20;

// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString] = {0};
////////////////////////////////////
#include "jalalidate.h"
char newDateString[40], oldDateString[40], oldTimerLocal[80], newTimerLocal[50];
extern TIME_DATE_STR JalaliTimeDate;
void displayDate()
{
  /////////////// Main Clock /////////////////
  // time_t rawtime;
  // struct tm *info;
  ////////////////////////////////////////////
  struct tm *newtime;
  TIME_DATE_STR GtimeDate;

  time_t ltime;
  time(&ltime);
  newtime = localtime(&ltime);
  GtimeDate.Sec = newtime->tm_sec;
  GtimeDate.Min = newtime->tm_min;
  GtimeDate.Hour = newtime->tm_hour;
  GtimeDate.Day = newtime->tm_mday;
  GtimeDate.Mon = newtime->tm_mon;
  GtimeDate.Year = newtime->tm_year;

  JalaliTimeDate = Miladi2Shamsi(GtimeDate);

  char buffer[80];
  strftime(buffer, 80, "%s", newtime);
  //   strftime(buffer,80,"%x - %I:%M%p", info);
  // printf("Formatted date & time : |%s|\n", buffer );

  /////////////////////////////////////////////

  // strftime(buffer,80,"%T", info);
  // uint8_t a = info.tm_sec;

  // sprintf(newTimerLocal,"%s",);
  tft.fillRect(0, 200, 250, 110, ST7735_WHITE);

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(0.2);

  tft.setCursor(10, 220);
  tft.setTextColor(ST7735_WHITE);
  tft.print(oldTimerLocal);

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(0.2);

  tft.setCursor(10, 220);
  tft.setTextColor(ST7735_BLACK);
  // tft.print(newTimerLocal);
  tft.print(newtime);

  Serial.println(printLocalTime());
  // Serial.printf("%4u/%2u/%2u    %2u:%2u:%2u\r\n", JalaliTimeDate.Year, JalaliTimeDate.Mon, JalaliTimeDate.Day, JalaliTimeDate.Hour, JalaliTimeDate.Min, JalaliTimeDate.Sec);
  strcpy(oldTimerLocal, buffer);
  // strcpy(oldDateString,newDateString);

  //}
}
////////////////// Date Setup End ////////////////////

char newTempString[30], oldTempString[30];

void displayTempData()
{
  float tempC = GetTemp();
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  sprintf(newTempString, "%.1f", tempC);

  tft.setFont(&nexa_black15pt7b);
  tft.setTextSize(2);

  int frontcolor = 0;
  int middlecolor = 0;
  int middle2color = 0;
  int backcolor = 0;
  int TextBGcolorTR = 0;
  int Textcolor = 0;
  if (tempC <= 20)
  {
    frontcolor = 0xffff;

    middlecolor = 0x5f5f;
    middle2color = 0x1f1f;
    //  backcolor = 0xffff;
    Textcolor = 0x1c1c;

    TextBGcolorTR = 0xffff;
  }
  else if (tempC > 20 && tempC <= 30)
  {
    frontcolor = 0xffff;

    middlecolor = 0xe6e6;
    middle2color = 0xe7e7;
    // backcolor = 0xe5e5;
    Textcolor = 0xa3a3;

    TextBGcolorTR = 0xffff;
  }
  else if (tempC > 30 && tempC <= 40)
  {
    frontcolor = 0xffff;

    middlecolor = 0xe2e2;
    middle2color = 0xe1e1;
    // backcolor = 0xc1c1;
    Textcolor = 0xe3e3;

    TextBGcolorTR = 0xffff;
  }
  else if (tempC > 40)
  {
    frontcolor = 0xffff;

    middlecolor = 0xa0a0;
    middle2color = 0xc0c0;
    //  backcolor = 0x8080;
    Textcolor = 0xa0a0;

    TextBGcolorTR = 0xffff;
  }

  int centerverticallalign = tft.width() / 2 - 15;
  int posdo = tft.height() / 2 - 70;
  int position1 = 0;
  int pos = 0;
  int nTemp = atoi(newTempString);
  if (nTemp % 2 == 0)
  {
    pos = tft.height() / 2 - 25;
  }
  else
  {
    pos = tft.height() / 2 - 20;
  }

  tft.fillCircle(120, -20, 150, middlecolor);
  // tft.fillCircle(120, centerverticallalign, 85, backcolor);
  tft.fillCircle(120, centerverticallalign, 90, middle2color);
  tft.fillCircle(120, centerverticallalign, 80, ST7735_WHITE);

  // yes! home the cursor
  tft.setCursor(posdo, centerverticallalign + 20);

  // change the text color to the background color
  tft.setTextColor(TextBGcolorTR);

  // redraw the old value to erase
  tft.print(oldTempString);

  //
  tft.setFont(&nexa_black15pt7b);

  tft.setTextSize(2);
  // tft.fillRect (0,0,240,100,Display_Color_Cyan);
  //  yes! home the cursor
  tft.setCursor(posdo, centerverticallalign + 25);

  // change the text color to the background color
  tft.setTextColor(Textcolor);

  tft.print(newTempString);

  strcpy(oldTempString, newTempString);
}

void logopr()
{
  // iconCheck();

  tft.setFont(&FreeSerifBold9pt7b);
  tft.setTextSize(0.2);

  tft.setCursor(5, 20);
  tft.setTextColor(Display_Color_White);
  tft.print("DS");
}

void newwrap()
{
  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextSize(0.2);

  tft.setCursor(40, 190);
  tft.setTextColor(Display_Color_DarkCyan);
  tft.print("Temperature");
}

void setupLCD()
{

  ///

  ///

  // settling time
  delay(250);

  // ignore any power-on-reboot garbage

#ifdef ADAFRUIT_HALLOWING
  // HalloWing is a special case. It uses a ST7735R display just like the
  // breakout board, but the orientation and backlight control are different.
  tft.initR(INITR_HALLOWING); // Initialize HalloWing-oriented screen
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
#else

  // OR use this initializer (uncomment) if using a 1.54" 240x240 TFT:
  tft.init(240, 240); // Init ST7789 240x240

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  // tft.setSPISpeed(40000000);
#endif

  // initialise the display
  tft.setFont(&FreeMono9pt7b);
  tft.setRotation(1);
  tft.fillScreen(Display_Backround_Color);
  tft.setTextColor(Display_Text_Color);
  tft.setTextSize(0.5);

  // the display is now on
  isDisplayVisible = true;
}

String readBattery()
{
  uint8_t percentage = 100;
  // float voltage = analogRead(35) / 4096.0 * 7.23; // LOLIN D32 (no voltage divider need already fitted to board.or NODEMCU ESP32 with 100K+100K voltage divider
  float voltage = analogRead(36) / 4096.0 * 7.23; // NODEMCU ESP32 with 100K+100K voltage divider added
  // float voltage = analogRead(A0) / 4096.0 * 4.24;    // Wemos / Lolin D1 Mini 100K series resistor added
  // float voltage = analogRead(A0) / 4096.0 * 5.00;    // Ardunio UNO, no voltage divider required
  Serial.println("Voltage = " + String(voltage)); // The voltage here needs to be reasonably accurate for a full LiFePO4 battery ~ 3.4v
  percentage = 4984.6172 * pow(voltage, 3) - 48287.7528 * pow(voltage, 2) + 155490.3329 * voltage - 166375.8607;
  if (voltage > 3.4)
    percentage = 100;
  else if (voltage <= 3.00)
    percentage = 0;
  // return String(percentage) + "%";
  return String(percentage);
}

void battericon()
{

  float voltage = analogRead(36) / 4096.0 * 7.23;
  int positionnew = tft.height() - 40;
  int positionnewx = 10;

  // tft.drawRect(tft.height() - 15, positionnewx + 2.5, 10, 10, 0xFFFF);
  //  tft.fillRect(tft.height() - 45, positionnewx +5, 15, 5, 0xFFFF);
  tft.drawRect(positionnew, positionnewx, 30, 15, 0xFFFF);
  if (voltage > 2.5 && voltage <= 3.3)
  {
    tft.fillRect(positionnew, positionnewx, 25, 15, 0xFFFF);
  }
  else if (voltage > 2 && voltage <= 2.5)
  {
    tft.fillRect(positionnew, positionnewx, 20, 15, 0xFFFF);
  }

  else if (voltage > 1.5 && voltage <= 2)
  {
    tft.fillRect(positionnew, positionnewx, 15, 15, 0xFFFF);
  }
  else if (voltage > 1 && voltage <= 1.5)
  {
    tft.fillRect(positionnew, positionnewx, 10, 15, 0xFFFF);
  }
  else if (voltage > 0.5 && voltage <= 1)
  {
    tft.fillRect(positionnew, positionnewx, 5, 15, 0xFFFF);
  }
  else if (voltage > 0 && voltage <= 0.5)
  {
    tft.fillRect(positionnew, positionnewx, 2, 15, 0xFFFF);
  }

  // switch (voltage)
  // {
  // case 2...3:
  //   tft.fillRect(10, 10, 20, 30, ST7735_GREEN);
  //   break;
  // case 1...2:
  //   tft.fillRect(10, 10, 20, 20, ST7735_GREEN);
  //   break;
  // case 0...1:
  //   tft.fillRect(10, 10, 20, 10, ST7735_GREEN);
  //   break;
  // default:
  //   break;
  // }
}

void monitorGrid()
{
  int grid = 10;
  int length = 240;
  int num = 0;
  while (num <= length)
  {
    num += length / grid;
    tft.fillRect(num, 0, 3, 240, ST7735_BLUE);
    tft.fillRect(0, num, 240, 3, ST7735_BLUE);
  }
}
