#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDialog>
#include <QListView>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "doCount.h"

class QListView;
class QStringListModel;

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = 0);
    ~window();

signals:

public slots:
    void timeOut();
private:
    QListView *listView;
    QStringListModel *model;

    QLabel *label_week2;
    QLabel *label_month2;
    QLabel *label_year2;

    doCount *date;
    oneRecord *records;
    QStringList timelist;
};

#endif // WINDOW_H
