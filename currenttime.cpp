#include "currenttime.h"

currentTime::currentTime()
{
    time_t t = time(0);
    char timebuf[10] = {0};

    strftime(timebuf, sizeof(timebuf), "%Y", localtime(&t));
    m_year = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%m", localtime(&t));
    m_month = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%d", localtime(&t));
    m_day = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%H", localtime(&t));
    m_hour = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%M", localtime(&t));
    m_minute = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%w", localtime(&t));
    m_week = atoi(timebuf);
}

currentTime::~currentTime()
{

}

int currentTime::year() const
{
    return m_year;
}

int currentTime::day() const
{
    return m_day;
}

int currentTime::month() const
{
    return m_month;
}

int currentTime::hour() const
{
    return m_hour;
}

int currentTime::minute() const
{
    return m_minute;
}

int currentTime::week() const
{
    return m_week;
}

bool currentTime::isRuinian()
{
    if((m_year % 400 == 0) || ((m_year % 4 == 0) && (m_year % 100 != 0)))
        return true;
    else
        return false;
}

