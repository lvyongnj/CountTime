#include "window.h"
#include <QObject>

window::window(QWidget *parent) : QWidget(parent)
{
    date = new doCount;
    date->counting();
    records = date->ht->getRecords();

//需要显示的数据添加
    for(int i = 0; i < date->ht->recordNum(); i++){
        QString s = QDateTime(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0)).toString("yyyy.MM.dd hh:mm")
            + "---" + QDateTime(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0)).toString("yyyy.MM.dd hh:mm");
        timelist << s;
        qDebug() << s;
        s.clear();
    }
//窗口布置及显示
    model = new QStringListModel(this);
    model->setStringList(timelist);
    listView = new QListView;
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked);

    QLabel *label_week1 = new QLabel("本周共使用：");
    label_week2 = new QLabel;
    QLabel *label_month1 = new QLabel("本月共使用：");
    label_month2 = new QLabel;
    QLabel *label_year1 = new QLabel("本年共使用：");
    label_year2 = new QLabel;

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

    char str[20];
    label_year2->setText(strcat(itoa(date->year(), str, 10), " 分钟"));
    label_month2->setText(strcat(itoa(date->month(), str, 10), " 分钟"));
    label_week2->setText(strcat(itoa(date->week(), str, 10), " 分钟"));

    QTimer *t = new QTimer;
    connect(t, SIGNAL(timeout()), this, SLOT(timeOut()));
    t->start(1000*30);
}

window::~window()
{
    delete date;
    delete model;
    delete listView;
}

void window::timeOut()
{
    date->counting();
    records = date->ht->getRecords();
    timelist.clear();

    for(int i = 0; i < date->ht->recordNum(); i++){
        QString s = QDateTime(QDate(records[i].yearBegin, records[i].monthBegin, records[i].dayBegin), QTime(records[i].hourBegin, records[i].minuteBegin, 0)).toString("yyyy.MM.dd hh:mm")
            + "---" + QDateTime(QDate(records[i].yearEnd, records[i].monthEnd, records[i].dayEnd), QTime(records[i].hourEnd, records[i].minuteEnd, 0)).toString("yyyy.MM.dd hh:mm");
        timelist << s;
        s.clear();
    }
    model->setStringList(timelist);
    listView->setModel(model);

    char str[20];
    label_year2->setText(strcat(itoa(date->year(), str, 10), " 分钟"));
    label_month2->setText(strcat(itoa(date->month(), str, 10), " 分钟"));
    label_week2->setText(strcat(itoa(date->week(), str, 10), " 分钟"));
}

