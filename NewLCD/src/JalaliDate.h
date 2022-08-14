
#ifndef _JALALIDATE_h
#define _JALALIDATE_h

#include <string.h>
#include <stdio.h>
#include "time.h"
#include <stdint.h>

typedef struct
{
  uint16_t Year;
  uint16_t Mon;
  uint16_t Day;
  uint16_t Hour;
  uint16_t Min;
  uint16_t Sec;
  uint16_t DayOfWeek;
  uint16_t DayOfYear;
  uint64_t UTCtime;
} TIME_DATE_STR;

/*****************************************************************************/
TIME_DATE_STR Shamsi2Miladi(TIME_DATE_STR Shamsi);
/*****************************************************************************/
TIME_DATE_STR Miladi2Shamsi(TIME_DATE_STR Miladi);
#endif
