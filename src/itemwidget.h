#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include "qpainter.h"
#include <QLabel>

class itemwidget : public QWidget
{
    Q_OBJECT
public:
    explicit itemwidget(QWidget *parent = nullptr);
    int item1count;
    int item2count;
    int item1rightcount;
    int item1leftcount;
    QVector<QPoint *> item1Positions;
    QVector<QPoint *> item2Positions;
    QVector<QPoint *> item1RightPositions;
    QVector<QPoint *> item1LeftPositions;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap item1(":/map/item2.png");
        QPixmap item2(":/map/item1.png");
        QPixmap item1right(":/map/item2right.png");
        QPixmap item1left(":/map/item2left.png");
        for (int var = 0; var < item1count; ++var) {
            QRect rect(item1Positions[var]->x(), item1Positions[var]->y(), 20, 20);
            painter.drawPixmap(rect, item1);
            //qDebug() << item1count;
        }
        for (int var = 0; var < item2count; ++var) {
            QRect rect(item2Positions[var]->x(), item2Positions[var]->y(), 20, 20);
            painter.drawPixmap(rect, item2);
        }
        for (int var = 0; var < item1rightcount; ++var) {
            QRect rect(item1RightPositions[var]->x(), item1RightPositions[var]->y(), 10, 20);
            painter.drawPixmap(rect, item1right);
        }
        for (int var = 0; var < item1leftcount; ++var) {
            QRect rect(item1LeftPositions[var]->x(), item1LeftPositions[var]->y(), 10, 20);
            painter.drawPixmap(rect, item1left);
        }
    }
signals:
};

#endif // ITEMWIDGET_H
