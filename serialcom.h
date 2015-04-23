#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtSerialPort/QtSerialPort>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class serialCom
{
public:
    serialCom();
    ~serialCom();
    bool openCom();
    bool writeToCom(short block = 0);
    bool readFromCom();

    QByteArray rcvData;

private:
    char command[19];
    QSerialPort *comport;
};

#endif // SERIALCOM_H
