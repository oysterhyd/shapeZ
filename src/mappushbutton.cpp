#include "mappushbutton.h"

MapPushButton::MapPushButton(QWidget *parent)
    : QPushButton{parent}
{
    init();
}


void MapPushButton::mousePressEvent(QMouseEvent *event) {
    emit clk(this->x(), this->y());
    if(event->button() == Qt::RightButton) {
        emit remove(this->x(), this->y());
    }
    QPushButton::mousePressEvent(event);
}

void MapPushButton::init() {
    IS_DIG_RIGHT = false;
    IS_DIG_LEFT = false;
    IS_DIG_UP = false;
    IS_DIG_DOWN = false;
    IS_CUT_UP_1 = false;
    IS_CUT_DOWN_1 = false;
    IS_CUT_RIGHT_1 = false;
    IS_CUT_LEFT_1 = false;
    IS_CUT_UP_2 = false;
    IS_CUT_DOWN_2 = false;
    IS_CUT_RIGHT_2 = false;
    IS_CUT_LEFT_2 = false;
    IS_PASS_RIGHT = false;
    IS_PASS_LEFT = false;
    IS_PASS_UP = false;
    IS_PASS_DOWN = false;
    IS_PASS_UPRIGHT = false;
    IS_PASS_RIGHTDOWN = false;
    IS_PASS_DOWNLEFT = false;
    IS_PASS_LEFTUP = false;
    IS_PASS_RIGHTUP = false;
    IS_PASS_UPLEFT = false;
    IS_PASS_LEFTDOWN = false;
    IS_PASS_DOWNRIGHT = false;
    IS_RUBBISH = false;
}




