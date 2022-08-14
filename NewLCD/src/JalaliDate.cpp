#include "JalaliDate.h"

/*****************************************************************************
** Function name:    Shamsi2Miladi
**
** Descriptions:    Convert Miladi Date To Shamsi
**
** parameters:      Miladi Date
** Returned value:  Shamsi Date
**
*****************************************************************************/
TIME_DATE_STR Shamsi2Miladi(TIME_DATE_STR Shamsi)
{
    uint8_t M_month, M_day, Cabise_Shmasi = 0, Res_Div;
    uint16_t M_year;
    TIME_DATE_STR Temp_Time;
    //----------------------------------
    M_year = (uint16_t)(Shamsi.Year);
    M_month = (uint8_t)(Shamsi.Mon);
    M_day = (uint8_t)(Shamsi.Day);

    Res_Div = M_year % 33;

    if ((Res_Div == 1) || (Res_Div == 5) || (Res_Div == 9) ||
        (Res_Div == 13) || (Res_Div == 18) || (Res_Div == 22) ||
        (Res_Div == 26) || (Res_Div == 30))
        Cabise_Shmasi = 1;

    if (Cabise_Shmasi)
    {
        if (--M_day == 0)
        {
            M_month--;
            if (M_month > 0 && M_month < 7)
                M_day = 31;
            else if (M_month > 6)
                M_day = 30;
            else if (M_month == 0)
            {
                M_day = 29;
                M_month = 12;
                M_year -= 1;
            }
        }
    }
    else
    {
        if (M_month == 12 && M_day == 10)
        {
            M_year += 622;
            M_month = 2;
            M_day = 29;
            goto Result_Calc;
        }
        else if (M_month == 12 && M_day > 10)
            M_day = M_day - 1;
    };

    if (M_month < 10 || (M_month == 10 && M_day < 11))
        M_year += 621;
    else
        M_year += 622;

    switch (M_month)
    {
    case 1:
        if (M_day < 12)
        {
            M_month = 3;
            M_day += 20;
        }
        else
        {
            M_month = 4;
            M_day -= 11;
        }
        break;
    case 2:
        if (M_day < 11)
        {
            M_month = 4;
            M_day += 20;
        }
        else
        {
            M_month = 5;
            M_day -= 10;
        }
        break;
    case 3:
        if (M_day < 11)
        {
            M_month = 5;
            M_day += 21;
        }
        else
        {
            M_month = 6;
            M_day -= 10;
        }
        break;
    case 4:
        if (M_day < 10)
        {
            M_month = 6;
            M_day += 21;
        }
        else
        {
            M_month = 7;
            M_day -= 9;
        }
        break;
    case 5:
    case 6:
    case 8:
        if (M_day < 10)
        {
            M_month += 2;
            M_day += 22;
        }
        else
        {
            M_month += 3;
            M_day -= 9;
        }
        break;
    case 7:
        if (M_day < 9)
        {
            M_month = 9;
            M_day += 22;
        }
        else
        {
            M_month = 10;
            M_day -= 8;
        }
        break;
    case 9:
        if (M_day < 10)
        {
            M_month = 11;
            M_day += 21;
        }
        else
        {
            M_month = 12;
            M_day -= 9;
        }
        break;
    case 10:
        if (M_day < 11)
        {
            M_month = 12;
            M_day += 21;
        }
        else
        {
            M_month = 1;
            M_day -= 10;
        }
        break;
    case 11:
        if (M_day < 12)
        {
            M_month = 1;
            M_day += 20;
        }
        else
        {
            M_month = 2;
            M_day -= 11;
        }
        break;
    case 12:
        if (M_day < 10)
        {
            M_month = 2;
            M_day += 19;
        }
        else
        {
            M_month = 3;
            M_day -= 9;
        }
        break;
    }

Result_Calc:
    Temp_Time.Sec = Shamsi.Sec;
    Temp_Time.Min = Shamsi.Min;
    Temp_Time.Hour = Shamsi.Hour;
    Temp_Time.DayOfWeek = Shamsi.DayOfWeek;
    Temp_Time.Year = M_year;
    Temp_Time.Mon = M_month;
    Temp_Time.Day = M_day;
    return (Temp_Time);
}

/*****************************************************************************
** Function name:   Miladi2Shamsi
**
** Descriptions:    Convert Miladi Date To Shamsi
**
** parameters:      RTCTime
** Returned value:    TimeL
**
*****************************************************************************/
TIME_DATE_STR Miladi2Shamsi(TIME_DATE_STR Miladi)
{
    TIME_DATE_STR Temp_Time;
    int ld, date;

    int miladiYear = Miladi.Year;
    int miladiMonth = Miladi.Mon;
    int miladiDate = Miladi.Day;

    const int buf1[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    const int buf2[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

    if ((miladiYear % 4) != 0)
    {
        date = buf1[miladiMonth - 1] + miladiDate;

        if (date > 79)
        {
            date = date - 79;
            if (date <= 186)
            {
                switch (date % 31)
                {
                case 0:
                    Temp_Time.Mon = date / 31;
                    date = 31;
                    break;
                default:
                    Temp_Time.Mon = (date / 31) + 1;
                    date = (date % 31);
                    break;
                }
                Temp_Time.Year = miladiYear - 621;
            }
            else
            {
                date = date - 186;

                switch (date % 30)
                {
                case 0:
                    Temp_Time.Mon = (date / 30) + 6;
                    date = 30;
                    break;
                default:
                    Temp_Time.Mon = (date / 30) + 7;
                    date = (date % 30);
                    break;
                }
                Temp_Time.Year = miladiYear - 621;
            }
        }
        else
        {
            if ((miladiYear > 1996) && (miladiYear % 4) == 1)
            {
                ld = 11;
            }
            else
            {
                ld = 10;
            }
            date = date + ld;

            switch (date % 30)
            {
            case 0:
                Temp_Time.Mon = (date / 30) + 9;
                date = 30;
                break;
            default:
                Temp_Time.Mon = (date / 30) + 10;
                date = (date % 30);
                break;
            }
            Temp_Time.Year = miladiYear - 622;
        }
    }
    else
    {
        date = buf2[miladiMonth - 1] + miladiDate;

        if (miladiYear >= 1996)
        {
            ld = 79;
        }
        else
        {
            ld = 80;
        }
        if (date > ld)
        {
            date = date - ld;

            if (date <= 186)
            {
                switch (date % 31)
                {
                case 0:
                    Temp_Time.Mon = (date / 31);
                    date = 31;
                    break;
                default:
                    Temp_Time.Mon = (date / 31) + 1;
                    date = (date % 31);
                    break;
                }
                Temp_Time.Year = miladiYear - 621;
            }
            else
            {
                date = date - 186;

                switch (date % 30)
                {
                case 0:
                    Temp_Time.Mon = (date / 30) + 6;
                    date = 30;
                    break;
                default:
                    Temp_Time.Mon = (date / 30) + 7;
                    date = (date % 30);
                    break;
                }
                Temp_Time.Year = miladiYear - 621;
            }
        }

        else
        {
            date = date + 10;

            switch (date % 30)
            {
            case 0:
                Temp_Time.Mon = (date / 30) + 9;
                date = 30;
                break;
            default:
                Temp_Time.Mon = (date / 30) + 10;
                date = (date % 30);
                break;
            }
            Temp_Time.Year = miladiYear - 622;
        }
    }

    Temp_Time.Sec = Miladi.Sec;
    Temp_Time.Min = Miladi.Min;
    Temp_Time.Hour = Miladi.Hour;
    Temp_Time.DayOfWeek = Miladi.DayOfWeek;
    Temp_Time.Day = date;
    return (Temp_Time);
}