#include "querytime.h"

querytime::querytime(QObject *parent) : QObject(parent)
{
    comport = new QSerialPort();
    isOpen = 0;

    command[0]=0x54;
    command[1]=0x58;
    command[2]=0x4c;
    command[3]=0x45;
    command[4]=0x44;
    command[5]=0x43;
    command[6]=0x4f;
    command[7]=0x4e;
    command[8]=0x54;
    command[9]=0x52;
    command[10]=0x4f;
    command[11]=0x4c;
    command[12]=0x4c;
    command[13]=0x45;
    command[14]=0x52;
    command[15]=0xbb;
    command[16]=0x07;
    command[17]=0x00;
    command[18]=0x40;
}

querytime::~querytime()
{
    delete comport;
}

bool querytime::openCom() {
    if (comport->isOpen()) {
        return true;
    }
    int flag = 0;
    comport->setDataBits(QSerialPort::Data8);
    comport->setParity(QSerialPort::NoParity);
    comport->setStopBits(QSerialPort::OneStop);
    comport->setBaudRate(QSerialPort::Baud115200);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        comport->setPortName(info.portName());
        comport->open(QIODevice::ReadWrite);
        comport->write(command, 19);
        while (comport->waitForReadyRead(100))
             rcvData.append(comport->readAll());
        if(!strncmp("run.log", rcvData.data(), 7)){
            flag = 1;
            isOpen = true;
            break;
        }
    }
    if(flag == 0)
        return false;
    else
        return true;
}

bool querytime::writeToCom(short block)
{
    rcvData.clear();
    command[18] = 0x40+block;
    openCom();
    comport->write(command, 19);

    return true;
}

bool querytime::readFromCom()
{
    qDebug() << "Brush:" <<"send data success";

    while (comport->waitForReadyRead(100))
        rcvData.append(comport->readAll());

    return true;
}




