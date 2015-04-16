#ifndef QUERYTIME_H
#define QUERYTIME_H

#include <QObject>
#include <QMap>
#include <QtDebug>
#include <QtSerialPort/QtSerialPort>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

class querytime : public QObject
{
    Q_OBJECT
public:
    explicit querytime(QObject *parent = 0);
    ~querytime();
    bool openCom();
    bool writeToCom(short block = 0);
    bool readFromCom();

signals:

public slots:
public:
    char command[19];
    QSerialPort *comport;
    QByteArray rcvData;
    bool isOpen;
};

#endif // QUERYTIME_H
