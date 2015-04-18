#ifndef CURRENTTIME_H
#define CURRENTTIME_H

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

class currentTime
{
public:
    currentTime();
    ~currentTime();
    bool isRuinian();
    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int week() const;

private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_week;
};

#endif // CURRENTTIME_H
