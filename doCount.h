#ifndef COUNT_H
#define COUNT_H
#include "currenttime.h"
#include "historyTime.h"

class doCount
{
public:
    doCount();
    ~doCount();
    bool counting();
    int year() const;
    int month() const;
    int week() const;
    int day() const;

    historyTime *ht;

private:
    int m_year;
    int m_month;
    int m_week;
    int m_day;
    oneRecord *records;
    currentTime *ct;
};

#endif // COUNT_H
