#ifndef HISTORYTIME_H
#define HISTORYTIME_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "serialcom.h"

typedef struct {
    int yearBegin;
    int yearEnd;
    int monthBegin;
    int monthEnd;
    int dayBegin;
    int dayEnd;
    int hourBegin;
    int hourEnd;
    int minuteBegin;
    int minuteEnd;
} oneRecord;

class historyTime
{
public:
    historyTime();
    ~historyTime();

    bool his();
    oneRecord *getRecords();
    int recordNum() const;

private:
    int m_recordNum;
    oneRecord *records;
    serialCom *com;
};

#endif // HISTORYTIME_H
