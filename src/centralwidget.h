#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "qpainter.h"

class centralwidget : public QWidget
{
    Q_OBJECT
public:
    explicit centralwidget(QWidget *parent = nullptr);
    int item1count;
    int item2count;
    QVector<QPoint *> item1Positions;
    QVector<QPoint *> item2Positions;
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap item1(":/map/item1.png");
        QPixmap item2(":/map/item2.png");
        for (int var = 0; var < item1count; ++var) {
            QRect rect(item1Positions[var]->x(), item1Positions[var]->y(), 20, 20);
            painter.drawPixmap(rect, item1);
            QWidget::paintEvent(event);
            qDebug() << item1count;
        }
        for (int var = 0; var < item2count; ++var) {
            QRect rect(item2Positions[var]->x(), item2Positions[var]->y(), 20, 20);
            painter.drawPixmap(rect, item2);
            QWidget::paintEvent(event);
        }
    }
signals:
};

#endif // CENTRALWIDGET_H
