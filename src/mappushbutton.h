#ifndef MAPPUSHBUTTON_H
#define MAPPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>


class MapPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MapPushButton(QWidget *parent = nullptr);

    bool IS_DIG_RIGHT;
    bool IS_DIG_LEFT;
    bool IS_DIG_UP;
    bool IS_DIG_DOWN;
    bool IS_CUT_UP_1;
    bool IS_CUT_DOWN_1;
    bool IS_CUT_RIGHT_1;
    bool IS_CUT_LEFT_1;
    bool IS_CUT_UP_2;
    bool IS_CUT_DOWN_2;
    bool IS_CUT_RIGHT_2;
    bool IS_CUT_LEFT_2;
    bool IS_PASS_RIGHT;
    bool IS_PASS_LEFT;
    bool IS_PASS_UP;
    bool IS_PASS_DOWN;
    bool IS_PASS_UPRIGHT;
    bool IS_PASS_RIGHTDOWN;
    bool IS_PASS_DOWNLEFT;
    bool IS_PASS_LEFTUP;
    bool IS_PASS_RIGHTUP;
    bool IS_PASS_UPLEFT;
    bool IS_PASS_LEFTDOWN;
    bool IS_PASS_DOWNRIGHT;
    bool IS_RUBBISH;
    void init();
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clk(int x, int y);
    void remove(int x, int y);
};

#endif // MAPPUSHBUTTON_H
