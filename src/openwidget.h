#ifndef OPENWIDGET_H
#define OPENWIDGET_H

#include <QWidget>
#include <Qpushbutton>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QFont>
#include "mainwindow.h"


class OpenWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
public:

    explicit OpenWidget(QWidget *parent = nullptr);
    void exit();
    void start();
    void readsave();
signals:
};

#endif // OPENWIDGET_H
