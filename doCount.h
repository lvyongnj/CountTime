#ifndef COUNT_H
#define COUNT_H
#include "currenttime.h"
#include "historyTime.h"

class doCount
{
public:
    doCount();
    ~doCount();

    int year() const;
    int month() const;
    int week() const;
    int day() const;

    bool counting();
    int time2time(int, int, int, int, int, int, int, int, int, int);//依次为：起始的年、月、日、时、分，结束的年、月、日、时、分。

    historyTime *ht;
    int in2timeNum; //有几段记录在查询时间之间
    int in2timeRec[100];

private:
    int m_year;
    int m_month;
    int m_week;
    int m_day;
    oneRecord *records;
    currentTime *ct;
};

#endif // COUNT_H
