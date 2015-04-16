#include "maincount.h"
#include <QFile>
#include <QTextStream>
#include <stdlib.h>

mainCount::mainCount(QWidget *parent)
    : QWidget(parent)
{
    com = new querytime;
    hisTime = new historyTime[128];
//布置窗体
    listView = new QListView;
    QLabel *label_week1 = new QLabel("本周共使用：");
    QLabel *label_week2 = new QLabel;
    QLabel *label_month1 = new QLabel("本月共使用：");
    QLabel *label_month2 = new QLabel;
    QLabel *label_year1 = new QLabel("本年共使用：");
    QLabel *label_year2 = new QLabel;

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(label_week1);
    hlayout1->addWidget(label_week2);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(label_month1);
    hlayout2->addWidget(label_month2);
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    hlayout3->addWidget(label_year1);
    hlayout3->addWidget(label_year2);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(listView);
    mainlayout->addLayout(vlayout);
    setLayout(mainlayout);

    setWindowTitle("Count Time");
//读取数据
    timeNum = 0;
    for(int n = 0; n <=15; n++)
    {
        com->writeToCom(n);
        com->readFromCom();

        char * buf;
        buf = com->rcvData.data();
        char *buff = new char[32];

        if(n == 0){
            for(int i = 1; i <= 7; i++){
                memset(buff, 0, 32);
                memcpy(buff, (buf+32*i), 4);
                if(!strcmp(buff, "run@"))
                {
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i), 29);
                    timelist << buff;   //添加到view显示

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+4), 4);
                    hisTime[timeNum].yearBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+8), 2);
                    hisTime[timeNum].monthBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+10), 2);
                    hisTime[timeNum].dayBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+12), 2);
                    hisTime[timeNum].hourBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+14), 2);
                    hisTime[timeNum].minuteBegin = atoi(buff);

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+17), 4);
                    hisTime[timeNum].yearEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+21), 2);
                    hisTime[timeNum].monthEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+23), 2);
                    hisTime[timeNum].dayEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+25), 2);
                    hisTime[timeNum].hourEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+27), 2);
                    hisTime[timeNum].minuteEnd = atoi(buff);

                    timeNum++;
                }
            }
        }else{
            for(int i = 0; i <= 7; i++){
                memset(buff, 0, 32);
                memcpy(buff, (buf+32*i), 4);
                if(!strcmp(buff, "run@"))
                {
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i), 29);
                    timelist << buff;

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+4), 4);
                    hisTime[timeNum].yearBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+8), 2);
                    hisTime[timeNum].monthBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+10), 2);
                    hisTime[timeNum].dayBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+12), 2);
                    hisTime[timeNum].hourBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+14), 2);
                    hisTime[timeNum].minuteBegin = atoi(buff);

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+17), 4);
                    hisTime[timeNum].yearEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+21), 2);
                    hisTime[timeNum].monthEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+23), 2);
                    hisTime[timeNum].dayEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+25), 2);
                    hisTime[timeNum].hourEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+27), 2);
                    hisTime[timeNum].minuteEnd = atoi(buff);

                    timeNum++;
                }
            }
        }

        //写入到文件
/*        QFile file("result.txt");
        if(!file.open(QIODevice::WriteOnly)){
            cout << "can not open" << endl;
        }
        QTextStream out(&file);
        out << buf << endl;
       // for(int i = 0; i < 256; i++){

        //}
*/
        FILE *file = fopen("resule.txt","aw+");
        fwrite(buf, 32, 8, file);
        fwrite("\n", 1, 1, file);
        fclose(file);

    }
//统计数据    
    time_t t = time(0);
    int year, month, day, hour, minute, week;
    char timebuf[10] = {0};

    strftime(timebuf, sizeof(timebuf), "%Y", localtime(&t));
    year = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%m", localtime(&t));
    month = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%d", localtime(&t));
    day = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%H", localtime(&t));
    hour = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%M", localtime(&t));
    minute = atoi(timebuf);
    strftime(timebuf, sizeof(timebuf), "%w", localtime(&t));
    week = atoi(timebuf);

    int countYear = 0, countMonth = 0, countWeek = 0;

    int isRuinian = 0;
    if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
        isRuinian = 1;
/*
    QDateTime a(QDate(2015, 5, 4), QTime(0, 0, 0));
    QDateTime b(QDate(2015, 5, 5), QTime(1, 7, 0));
    int aa = a.daysTo(b);
    aa = a.secsTo(b)/60;
    //aa = a.
*/
    for(int i = 0; i < timeNum; i++){
        if(hisTime[i].yearEnd == year){
            if(hisTime[i].monthEnd == month){
                if(hisTime[i].yearBegin != year)
                    countMonth += ((hisTime[i].dayEnd-1) * 24 * 60 + hisTime[i].hourEnd * 60 + hisTime[i].minuteEnd);
                else if(hisTime[i].monthBegin != month)
                    countMonth += ((hisTime[i].dayEnd-1) * 24 * 60 + hisTime[i].hourEnd * 60 + hisTime[i].minuteEnd);
                else
                    countMonth += ((hisTime[i].dayEnd - hisTime[i].dayBegin)*24*60 + hisTime[i].hourEnd*60 + hisTime[i].minuteEnd - hisTime[i].hourBegin*60 - hisTime[i].minuteBegin);
             }
             if(hisTime[i].yearBegin != year){
                for(int j = 1; j < hisTime[i].monthEnd; j++){
                    switch (j) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        countYear += 31 * 24 * 60;
                        break;
                    case 2:
                    {
                        if(isRuinian)
                            countYear += 29 * 24 * 60;
                        else
                            countYear += 28 * 24 * 60;
                    }
                        break;
                    default:
                        countYear += 30 * 24 * 60;
                        break;
                    }
                }
                countYear += ((hisTime[i].dayEnd-1) * 24 * 60 + hisTime[i].hourEnd* 60 + hisTime[i].minuteEnd);
            }
            else{
                for(int j = hisTime[i].monthBegin; j < hisTime[i].monthEnd; j++){
                    switch (j) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        countYear += 31 * 24 * 60;
                        break;
                    case 2:
                    {
                        if(isRuinian)
                            countYear += 29 * 24 * 60;
                        else
                            countYear += 28 * 24 * 60;
                    }
                        break;
                    default:
                        countYear += 30 * 24 * 60;
                        break;
                    }
                }
                countYear += ((hisTime[i].dayEnd-1)*24*60 + hisTime[i].hourEnd*60 + hisTime[i].minuteEnd - (hisTime[i].dayBegin-1)*24*60 - hisTime[i].hourBegin*60 - hisTime[i].minuteBegin);
            }
        }
        if(day < (week+1)){
            switch (month) {
                case 1:
                {
                    if(((hisTime[i].yearEnd==(year-1))&&(hisTime[i].monthEnd==12)&&(hisTime[i].dayEnd>=(31-week+day))) || (hisTime[i].yearEnd==year)){
                        if(((hisTime[i].yearBegin==(year-1))&&(hisTime[i].monthBegin==12)&&(hisTime[i].dayBegin>=(31-week+day))) || (hisTime[i].yearBegin==year)){
                            QDateTime a(QDate(hisTime[i].yearBegin, hisTime[i].monthBegin, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate((year-1), 12, (31-week+day)), QTime(0, 0, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
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
                    if((hisTime[i].yearEnd==year) && ((hisTime[i].monthEnd==month) || ((hisTime[i].monthEnd==(month-1))&&(hisTime[i].dayEnd>=(31-week+day)))))
                        if((hisTime[i].yearBegin==year) && ((hisTime[i].monthBegin==month) || ((hisTime[i].monthBegin==(month-1))&&(hisTime[i].dayBegin>=(31-week+day))))){
                            QDateTime a(QDate(hisTime[i].yearBegin, hisTime[i].monthBegin, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate(year, (month-1), (31-week+day)), QTime(0, 0, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
                        }
                }
                    break;
                case 3:
                {
                    if(isRuinian){
                        if((hisTime[i].yearEnd==year) && ((hisTime[i].monthEnd==month) || ((hisTime[i].monthEnd==(month-1))&&(hisTime[i].dayEnd>=(28-week+day)))))
                            if((hisTime[i].yearBegin==year) && ((hisTime[i].monthBegin==month) || ((hisTime[i].monthBegin==(month-1))&&(hisTime[i].dayBegin>=(28-week+day))))){
                                QDateTime a(QDate(hisTime[i].yearBegin, hisTime[i].monthBegin, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                                QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                                countWeek += a.secsTo(b)/60;
                            }
                            else{
                                QDateTime a(QDate(year, (month-1), (28-week+day)), QTime(0, 0, 0));
                                QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                                countWeek += a.secsTo(b)/60;
                            }
                    }
                    else{
                        if((hisTime[i].yearEnd==year) && ((hisTime[i].monthEnd==month) || ((hisTime[i].monthEnd==(month-1))&&(hisTime[i].dayEnd>=(29-week+day)))))
                            if((hisTime[i].yearBegin==year) && ((hisTime[i].monthBegin==month) || ((hisTime[i].monthBegin==(month-1))&&(hisTime[i].dayBegin>=(29-week+day))))){
                                QDateTime a(QDate(hisTime[i].yearBegin, hisTime[i].monthBegin, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                                QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                                countWeek += a.secsTo(b)/60;
                            }
                            else{
                                QDateTime a(QDate(year, (month-1), (29-week+day)), QTime(0, 0, 0));
                                QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                                countWeek += a.secsTo(b)/60;
                            }
                    }
                }
                    break;
                default:
                {
                    if((hisTime[i].yearEnd==year) && ((hisTime[i].monthEnd==month) || ((hisTime[i].monthEnd==(month-1))&&(hisTime[i].dayEnd>=(30-week+day)))))
                        if((hisTime[i].yearBegin==year) && ((hisTime[i].monthBegin==month) || ((hisTime[i].monthBegin==(month-1))&&(hisTime[i].dayBegin>=(30-week+day))))){
                            QDateTime a(QDate(hisTime[i].yearBegin, hisTime[i].monthBegin, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
                        }
                        else{
                            QDateTime a(QDate(year, (month-1), (30-week+day)), QTime(0, 0, 0));
                            QDateTime b(QDate(hisTime[i].yearEnd, hisTime[i].monthEnd, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                            countWeek += a.secsTo(b)/60;
                        }
                }
                    break;
            }
        }
        else{
            if((hisTime[i].yearEnd == year) && (hisTime[i].monthEnd == month) && (hisTime[i].dayEnd >= (day-week))){
                if((hisTime[i].yearEnd == year) && (hisTime[i].monthEnd == month) && (hisTime[i].dayEnd >= (day-week))){
                    QDateTime a(QDate(year, month, hisTime[i].dayBegin), QTime(hisTime[i].hourBegin, hisTime[i].minuteBegin, 0));
                    QDateTime b(QDate(year, month, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                    countWeek += a.secsTo(b)/60;
                }
                else{
                    QDateTime a(QDate(year, month, (day-week)), QTime(0, 0, 0));
                    QDateTime b(QDate(year, month, hisTime[i].dayEnd), QTime(hisTime[i].hourEnd, hisTime[i].minuteEnd, 0));
                    countWeek += a.secsTo(b)/60;
                }
             }
        }
    }

//显示数据
    model = new QStringListModel(this);
    model->setStringList(timelist);
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked);

    char str[20];
    label_year2->setText(strcat(itoa(countYear, str, 10), " 分钟"));
    label_month2->setText(strcat(itoa(countMonth, str, 10), " 分钟"));
    label_week2->setText(strcat(itoa(countWeek, str, 10), " 分钟"));
//关闭串口
    com->comport->close();
}


mainCount::~mainCount()
{
    delete com;
    delete model;
    delete listView;
}
