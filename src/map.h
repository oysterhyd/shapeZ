#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>
#include "mappushbutton.h"
#include "itemwidget.h"

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    QVector<MapPushButton *> buttons;
    void mapupdate();
    int center_imin;
    int center_jmin;
    int length;
    // int item1count;
    // int item2count;
    // QVector<QPoint *> item1Positions;
    // QVector<QPoint *> item2Positions;
    itemwidget *i;
protected:
    // void paintEvent(QPaintEvent *event) override {
    //     QPainter painter(this);
    //     QPixmap item1(":/map/item1.png");
    //     QPixmap item2(":/map/item2.png");
    //     QRect rect(0, 0, 20, 20);
    //     painter.drawPixmap(rect, item1);
    //     for (int var = 0; var < item1count; ++var) {
    //         QRect rect(item1Positions[var]->x(), item1Positions[var]->y(), 20, 20);
    //         painter.drawPixmap(rect, item1);
    //         qDebug() << item1count;
    //     }
    //     for (int var = 0; var < item2count; ++var) {
    //         QRect rect(item2Positions[var]->x(), item2Positions[var]->y(), 20, 20);
    //         painter.drawPixmap(rect, item2);
    //     }
    // }
};

#endif // MAP_H
