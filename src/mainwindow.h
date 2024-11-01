#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "map.h"
#include <QtMath>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

static bool IS_DIG_RIGHT_STATE = false;
static bool IS_DIG_LEFT_STATE = false;
static bool IS_DIG_UP_STATE = false;
static bool IS_DIG_DOWN_STATE = false;
static bool IS_CUT_UP_STATE = false;
static bool IS_CUT_DOWN_STATE = false;
static bool IS_CUT_RIGHT_STATE = false;
static bool IS_CUT_LEFT_STATE = false;
static bool IS_PASS_RIGHT_STATE = false;
static bool IS_PASS_LEFT_STATE = false;
static bool IS_PASS_UP_STATE = false;
static bool IS_PASS_DOWN_STATE = false;
static bool IS_PASS_RIGHTUP_STATE = false;
static bool IS_PASS_UPLEFT_STATE = false;
static bool IS_PASS_LEFTDOWN_STATE = false;
static bool IS_PASS_DOWNRIGHT_STATE = false;
static bool IS_PASS_RIGHTDOWN_STATE = false;
static bool IS_PASS_DOWNLEFT_STATE = false;
static bool IS_PASS_LEFTUP_STATE = false;
static bool IS_PASS_UPRIGHT_STATE = false;
static bool IS_RUBBISH_STATE = false;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void is_dig_right_state();
    void is_dig_left_state();
    void is_dig_up_state();
    void is_dig_down_state();
    void is_cut_up_state();
    void is_cut_down_state();
    void is_cut_right_state();
    void is_cut_left_state();
    void is_pass_right_state();
    void is_pass_left_state();
    void is_pass_up_state();
    void is_pass_down_state();
    void is_pass_rightup_state();
    void is_pass_upleft_state();
    void is_pass_leftdown_state();
    void is_pass_downright_state();
    void is_pass_rightdown_state();
    void is_pass_downleft_state();
    void is_pass_leftup_state();
    void is_pass_upright_state();
    void is_rubbish_state();
    void put(int x, int y);
    void Remove(int x, int y);
    void generate();
    void cutgenerate();
    void updatePosition();
    void cutupdatePosition();
    void numupdate();
    int receiveditem1;
    int receiveditem2;
    int receiveditem1left;
    int receiveditem1right;
    void save();
    Map *map;
    int t_1;
    int t_2;
    int t_3;
    int coinnum;
    int value;
    void levelup1();
    void levelup2();
    void levelup3();
    void levelup4();
    void levelup5();
signals:
private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
};

#endif // MAINWINDOW_H
