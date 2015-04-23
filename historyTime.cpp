#include "historyTime.h"

historyTime::historyTime()
    :m_recordNum(0)
{
    com = new serialCom;
    com->openCom();
}

historyTime::~historyTime()
{
    delete [] records;
    delete com;
}

bool historyTime::his()
{
    m_recordNum = 0;
    if(records != NULL)
        delete records;
    records = new oneRecord[128];

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
                    memcpy(buff, (buf+32*i+4), 4);
                    records[m_recordNum].yearBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+8), 2);
                    records[m_recordNum].monthBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+10), 2);
                    records[m_recordNum].dayBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+12), 2);
                    records[m_recordNum].hourBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+14), 2);
                    records[m_recordNum].minuteBegin = atoi(buff);

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+17), 4);
                    records[m_recordNum].yearEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+21), 2);
                    records[m_recordNum].monthEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+23), 2);
                    records[m_recordNum].dayEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+25), 2);
                    records[m_recordNum].hourEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+27), 2);
                    records[m_recordNum].minuteEnd = atoi(buff);

                    m_recordNum++;
                }
            }
        }else{
            for(int i = 0; i <= 7; i++){
                memset(buff, 0, 32);
                memcpy(buff, (buf+32*i), 4);
                if(!strcmp(buff, "run@"))
                {
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+4), 4);
                    records[m_recordNum].yearBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+8), 2);
                    records[m_recordNum].monthBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+10), 2);
                    records[m_recordNum].dayBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+12), 2);
                    records[m_recordNum].hourBegin = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+14), 2);
                    records[m_recordNum].minuteBegin = atoi(buff);

                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+17), 4);
                    records[m_recordNum].yearEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+21), 2);
                    records[m_recordNum].monthEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+23), 2);
                    records[m_recordNum].dayEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+25), 2);
                    records[m_recordNum].hourEnd = atoi(buff);
                    memset(buff, 0, 32);
                    memcpy(buff, (buf+32*i+27), 2);
                    records[m_recordNum].minuteEnd = atoi(buff);

                    m_recordNum++;
                }
            }
        }
//写入文件
        FILE *file = fopen("resule.txt","aw+");
        fwrite(buf, 32, 8, file);
        fwrite("\n", 1, 1, file);
        fclose(file);
    }
    return true;
}

oneRecord *historyTime::getRecords()
{
    return records;
}

int historyTime::recordNum() const
{
    return m_recordNum;
}

