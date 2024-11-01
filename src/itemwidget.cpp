#include "itemwidget.h"

itemwidget::itemwidget(QWidget *parent)
    : QWidget{parent}, item1count(0), item2count(0), item1rightcount(0), item1leftcount(0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
    this->resize(1200, 800);
    label1 = new QLabel("物品1的数量：0", this);
    label2 = new QLabel("物品2的数量：0", this);
    label3 = new QLabel("物品1左的数量：0", this);
    label4 = new QLabel("物品1右的数量：0", this);
    label5 = new QLabel("金币的数量：0", this);
    label1->resize(120, 40);
    label2->resize(120, 40);
    label3->resize(120, 40);
    label4->resize(120, 40);
    label5->resize(120, 40);
    label1->move(560, 340);
    label2->move(560, 360);
    label3->move(560, 380);
    label4->move(560, 400);
    label5->move(560, 420);
}
