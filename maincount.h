#ifndef MAINCOUNT_H
#define MAINCOUNT_H

#include <QWidget>
#include <QLabel>
#include <QDialog>
#include <QListView>
#include <QStringListModel>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "querytime.h"

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
} historyTime;

class QListView;
class QStringListModel;

class mainCount : public QWidget
{
    Q_OBJECT

public:
    mainCount(QWidget *parent = 0);
    ~mainCount();

private:
    QListView *listView;
    QStringListModel *model;
    QStringList timelist;
    querytime *com;
    historyTime *hisTime;
    int timeNum; //历史时间记录个数
};

#endif // MAINCOUNT_H
