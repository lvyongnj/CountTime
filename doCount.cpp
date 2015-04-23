#include "doCount.h"

doCount::doCount()
    :m_year(0),m_month(0),m_week(0),m_day(0)
{
    ct = new currentTime;
    ht = new historyTime;
}

doCount::~doCount()
{

}

bool doCount::counting()
{
    m_year = 0;
    m_month = 0;
    m_week = 0;
    m_day = 0;
    ht->his();
    records = ht->getRecords();
    for(int i = 0; i < ht->recordNum(); i++){
        if(records[i].yearEnd == ct->year()){
            if(records[i].monthEnd == ct->month()){                 //统计本月
                if(records[i].yearBegin != ct->year())
                    m_month += ((records[i].dayEnd-1) * 24 * 60 + records[i].hourEnd * 60 + records[i].minuteEnd);
                else if(records[i].monthBegin != ct->month())
                    m_month += ((records[i].dayEnd-1) * 24 * 60 + records[i].hourEnd * 60 + records[i].minuteEnd);
                else
                    m_month += ((records[i].dayEnd - records[i].dayBegin)*24*60 + records[i].hourEnd*60 + records[i].minuteEnd - records[i].hourBegin*60 - records[i].minuteBegin);
                if(records[i].dayEnd == ct->day()){                 //统计今天
                    if(records[i].yearBegin != ct->year())
                        m_day += (records[i].hourEnd * 60 + records[i].minuteEnd);
                    else if(records[i].monthBegin != ct->month())
                        m_day += (records[i].hourEnd * 60 + records[i].minuteEnd);
                    else if(records[i].dayBegin != ct->day())
                        m_day += (records[i].hourEnd * 60 + records[i].minuteEnd);
                    else
                        m_day += (records[i].hourEnd * 60 + records[i].minuteEnd - records[i].hourBegin *60 - records[i].minuteBegin);
                }
             }
             if(records[i].yearBegin != ct->year()){
                for(int j = 1; j < records[i].monthEnd; j++){
                    switch (j) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        m_year += 31 * 24 * 60;
                        break;
                    case 2:
                    {
                        if(ct->isRuinian())
                            m_year += 29 * 24 * 60;
                        else
                            m_year += 28 * 24 * 60;
                    }
                        break;
                    default:
                        m_year += 30 * 24 * 60;
                        break;
                    }
                }
                m_year += ((records[i].dayEnd-1) * 24 * 60 + records[i].hourEnd* 60 + records[i].minuteEnd);
            }
            else{
                for(int j = records[i].monthBegin; j < records[i].monthEnd; j++){
                    switch (j) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        m_year += 31 * 24 * 60;
                        break;
                    case 2:
                    {
                        if(ct->isRuinian())
                            m_year += 29 * 24 * 60;
                        else
                            m_year += 28 * 24 * 60;
                    }
                        break;
                    default:
                        m_year += 30 * 24 * 60;
                        break;
                    }
                }
                m_year += ((records[i].dayEnd-1)*24*60 + records[i].hourEnd*60 + records[i].minuteEnd - (records[i].dayBegin-1)*24*60 - records[i].hourBegin*60 - records[i].minuteBegin);
            }
        }
        if(ct->day() < (ct->week()+1)){
            switch (ct->month()) {
                case 1:
                {
                    if(((records[i].yearEnd==(ct->year()-1))&&(records[i].monthEnd==12)&&(records[i].dayEnd>=(31-ct->week()+ct->day()))) || (records[i].yearEnd==ct->year())){
                        if(((records[i].yearBegin==(ct->year()-1))&&(records[i].monthBegin==12)&&(records[i].dayBegin>=(31-ct->week()+ct->day()))) || (records[i].yearBegin==ct->year())){
                            QDateTime a(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate((ct->year()-1), 12, (31-ct->week()+ct->day())), QTime(0, 0, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                    }
                }
                    break;
                case 2:
                case 4:
                case 6:
                case 8:
                case 9:
                case 11:
                {
                    if((records[i].yearEnd==ct->year()) && ((records[i].monthEnd==ct->month()) || ((records[i].monthEnd==(ct->month()-1))&&(records[i].dayEnd>=(31-ct->week()+ct->day()))))){
                        if((records[i].yearBegin==ct->year()) && ((records[i].monthBegin==ct->month()) || ((records[i].monthBegin==(ct->month()-1))&&(records[i].dayBegin>=(31-ct->week()+ct->day()))))){
                            QDateTime a(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate(ct->year(), (ct->month()-1), (31-ct->week()+ct->day())), QTime(0, 0, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                    }
                }
                    break;
                case 3:
                {
                    if(ct->isRuinian()){
                        if((records[i].yearEnd==ct->year()) && ((records[i].monthEnd==ct->month()) || ((records[i].monthEnd==(ct->month()-1))&&(records[i].dayEnd>=(28-ct->week()+ct->day()))))){
                            if((records[i].yearBegin==ct->year()) && ((records[i].monthBegin==ct->month()) || ((records[i].monthBegin==(ct->month()-1))&&(records[i].dayBegin>=(28-ct->week()+ct->day()))))){
                                QDateTime a(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                                QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                                m_week += a.secsTo(b)/60;
                            }
                            else{
                                QDateTime a(QDate(ct->year(), (ct->month()-1), (28-ct->week()+ct->day())), QTime(0, 0, 0));
                                QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                                m_week += a.secsTo(b)/60;
                            }
                        }
                    }
                    else{
                        if((records[i].yearEnd==ct->year()) && ((records[i].monthEnd==ct->month()) || ((records[i].monthEnd==(ct->month()-1))&&(records[i].dayEnd>=(29-ct->week()+ct->day()))))){
                            if((records[i].yearBegin==ct->year()) && ((records[i].monthBegin==ct->month()) || ((records[i].monthBegin==(ct->month()-1))&&(records[i].dayBegin>=(29-ct->week()+ct->day()))))){
                                QDateTime a(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                                QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                                m_week += a.secsTo(b)/60;
                            }
                            else{
                                QDateTime a(QDate(ct->year(), (ct->month()-1), (29-ct->week()+ct->day())), QTime(0, 0, 0));
                                QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                                m_week += a.secsTo(b)/60;
                            }
                        }
                    }
                }
                    break;
                default:
                {
                    if((records[i].yearEnd==ct->year()) && ((records[i].monthEnd==ct->month()) || ((records[i].monthEnd==(ct->month()-1))&&(records[i].dayEnd>=(30-ct->week()+ct->day()))))){
                        if((records[i].yearBegin==ct->year()) && ((records[i].monthBegin==ct->month()) || ((records[i].monthBegin==(ct->month()-1))&&(records[i].dayBegin>=(30-ct->week()+ct->day()))))){
                            QDateTime a(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate(ct->year(), (ct->month()-1), (30-ct->week()+ct->day())), QTime(0, 0, 0));
                            QDateTime b(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                            m_week += a.secsTo(b)/60;
                        }
                    }
                }
                    break;
            }
        }
        else{
            if((records[i].yearEnd == ct->year()) && (records[i].monthEnd == ct->month()) && (records[i].dayEnd >= (ct->day()-ct->week()))){
                if((records[i].yearEnd == ct->year()) && (records[i].monthEnd == ct->month()) && (records[i].dayEnd >= (ct->day()-ct->week()))){
                    QDateTime a(QDate(ct->year(),ct->month(), records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0));
                    QDateTime b(QDate(ct->year(),ct->month(), records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                    m_week += a.secsTo(b)/60;
                }
                else{
                    QDateTime a(QDate(ct->year(), ct->month(), (ct->day()-ct->week())), QTime(0, 0, 0));
                    QDateTime b(QDate(ct->year(), ct->month(), records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0));
                    m_week += a.secsTo(b)/60;
                }
             }
        }
    }
    return true;
}

int doCount::time2time(int yb, int Mb, int db, int hb, int mb, int ye, int Me, int de, int he, int me)
{
    int allTime = 0;
    in2timeNum = 0;
    QDateTime r(QDate(ct->year(),ct->month(),ct->day()), QTime(ct->hour(),ct->minute(),0));
    QDateTime b(QDate(yb, Mb, db), QTime(hb, mb, 0));
    QDateTime e(QDate(ye, Me, de), QTime(he, me, 0));
    if((b > e) || (b > r))
        return -1;
    for(int i = 0; i < ht->recordNum(); i++){
        QDateTime hb(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin,records[i].minuteBegin,0));
        QDateTime he(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd,records[i].minuteEnd,0));
        if(hb < b){
            if(he > e){
                allTime += b.secsTo(e)/60;
                in2timeRec[in2timeNum] = i;
                in2timeNum++;
            }
            else if(he > b){
                allTime += b.secsTo(he)/60;
                in2timeRec[in2timeNum] = i;
                in2timeNum++;
            }
        }
        else if(hb < e){
            if(he < e){
                allTime += hb.secsTo(he)/60;
                in2timeRec[in2timeNum] = i;
                in2timeNum++;
            }
            else{
                allTime += hb.secsTo(e)/60;
                in2timeRec[in2timeNum] = i;
                in2timeNum++;
            }
        }
   }

    return allTime;
}

int doCount::year() const
{
    return m_year;
}

int doCount::month() const
{
    return m_month;
}

int doCount::week() const
{
    return m_week;
}

int doCount::day() const
{
    return m_day;
}
