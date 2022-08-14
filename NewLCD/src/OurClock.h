#include <WiFi.h>
#include "time.h"
#include <TimeLib.h>
#include "jalalidate.h"

String timerLocal = "";
TIME_DATE_STR JalaliTimeDate;

String printLocalTime()
{
  /*
  struct tm *newtime;
  time_t ltime;
  time(&ltime);
  newtime = localtime(&ltime);

  return asctime(newtime);

  */

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

  return asctime(newtime);
}

const char *ssid = "Shayea";
const char *password = "@Amiriziy2016";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 16200;
const int daylightOffset_sec = 0;

/*
void printLocalTime()
{
 struct tm timeinfo;
 if(!getLocalTime(&timeinfo)){
   Serial.println("Failed to obtain time");
   return;
 }
 Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

}
*/
