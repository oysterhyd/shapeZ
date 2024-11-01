#include "openwidget.h"

void OpenWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/open/open.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    QWidget::paintEvent(event);
}

void OpenWidget::exit() {
    close();
}

void OpenWidget::start() {
    close();
    MainWindow *mainwindow = new MainWindow;
    mainwindow->resize(1200, 800);
    mainwindow->show();
}

void OpenWidget::readsave() {
    MainWindow *mainwindow = new MainWindow;
    mainwindow->resize(1200, 800);
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select a txt", QDir::homePath(), "All Files (*.*)");
    if(!filePath.isEmpty()) {
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        QTextStream outfile(&file);
        outfile >> mainwindow->map->i->item1count >> mainwindow->map->i->item2count
            >> mainwindow->map->i->item1rightcount >> mainwindow->map->i->item1leftcount >> mainwindow->receiveditem1
            >> mainwindow->receiveditem2 >> mainwindow->receiveditem1left
            >> mainwindow->receiveditem1right >> mainwindow->t_1 >> mainwindow->t_2 >> mainwindow->t_3
            >> mainwindow->coinnum >> mainwindow->value >> mainwindow->map->center_imin >> mainwindow->map->center_jmin >> mainwindow->map->length;
        for (int var = 0; var < mainwindow->map->i->item1count; ++var) {
            int i, j;
            outfile >> i;
            outfile >> j;
            QPoint *p = new QPoint(i ,j);
            mainwindow->map->i->item1Positions.push_back(p);
        }
        for (int var = 0; var < mainwindow->map->i->item2count; ++var) {
            int i, j;
            outfile >> i;
            outfile >> j;
            QPoint *p = new QPoint(i ,j);
            mainwindow->map->i->item2Positions.push_back(p);
        }
        for (int var = 0; var < mainwindow->map->i->item1leftcount; ++var) {
            int i, j;
            outfile >> i;
            outfile >> j;
            QPoint *p = new QPoint(i ,j);
            mainwindow->map->i->item1LeftPositions.push_back(p);
        }
        for (int var = 0; var < mainwindow->map->i->item1rightcount; ++var) {
            int i, j;
            outfile >> i;
            outfile >> j;
            QPoint *p = new QPoint(i ,j);
            mainwindow->map->i->item1RightPositions.push_back(p);
        }
        for (int var = 0; var < mainwindow->map->buttons.size(); ++var) {
            int i[25];
            for (int var = 0; var <25; ++var) {
                outfile >> i[var];
            }
            mainwindow->map->buttons[var]->IS_DIG_UP = i[0];
            mainwindow->map->buttons[var]->IS_DIG_DOWN = i[1];
            mainwindow->map->buttons[var]->IS_DIG_RIGHT = i[2];
            mainwindow->map->buttons[var]->IS_DIG_LEFT = i[3];
            mainwindow->map->buttons[var]->IS_CUT_UP_1 = i[4];
            mainwindow->map->buttons[var]->IS_CUT_UP_2 = i[5];
            mainwindow->map->buttons[var]->IS_CUT_DOWN_1 = i[6];
            mainwindow->map->buttons[var]->IS_CUT_DOWN_2= i[7];
            mainwindow->map->buttons[var]->IS_CUT_LEFT_1 = i[8];
            mainwindow->map->buttons[var]->IS_CUT_LEFT_2 = i[9];
            mainwindow->map->buttons[var]->IS_CUT_RIGHT_1 = i[10];
            mainwindow->map->buttons[var]->IS_CUT_RIGHT_2 = i[11];
            mainwindow->map->buttons[var]->IS_PASS_UP = i[12];
            mainwindow->map->buttons[var]->IS_PASS_DOWN = i[13];
            mainwindow->map->buttons[var]->IS_PASS_RIGHT = i[14];
            mainwindow->map->buttons[var]->IS_PASS_LEFT = i[15];
            mainwindow->map->buttons[var]->IS_PASS_UPRIGHT = i[16];
            mainwindow->map->buttons[var]->IS_PASS_UPLEFT = i[17];
            mainwindow->map->buttons[var]->IS_PASS_DOWNRIGHT = i[18];
            mainwindow->map->buttons[var]->IS_PASS_DOWNLEFT = i[19];
            mainwindow->map->buttons[var]->IS_PASS_RIGHTUP = i[20];
            mainwindow->map->buttons[var]->IS_PASS_RIGHTDOWN = i[21];
            mainwindow->map->buttons[var]->IS_PASS_LEFTUP = i[22];
            mainwindow->map->buttons[var]->IS_PASS_LEFTDOWN = i[23];
            mainwindow->map->buttons[var]->IS_RUBBISH = i[24];
        }
    }
    // std::fstream outfile;
    // outfile.open("C:/Users/72802/Desktop/project/ShapeZ/memory");
    // if(!outfile.is_open()) {
    //     qDebug() << "0";
    //     return;
    // }
    // outfile >> mainwindow->map->i->item1count >> mainwindow->map->i->item2count
    //     >> mainwindow->map->i->item1rightcount >> mainwindow->map->i->item1leftcount >> mainwindow->receiveditem1
    //     >> mainwindow->receiveditem2 >> mainwindow->receiveditem1left
    //     >> mainwindow->receiveditem1right >> mainwindow->t_1 >> mainwindow->t_2 >> mainwindow->t_3
    //     >> mainwindow->coinnum >> mainwindow->value >> mainwindow->map->center_imin >> mainwindow->map->center_jmin >> mainwindow->map->length;
    // for (int var = 0; var < mainwindow->map->i->item1count; ++var) {
    //     int i, j;
    //     outfile >> i;
    //     outfile >> j;
    //     QPoint *p = new QPoint(i ,j);
    //     mainwindow->map->i->item1Positions.push_back(p);
    // }
    // for (int var = 0; var < mainwindow->map->i->item2count; ++var) {
    //     int i, j;
    //     outfile >> i;
    //     outfile >> j;
    //     QPoint *p = new QPoint(i ,j);
    //     mainwindow->map->i->item2Positions.push_back(p);
    // }
    // for (int var = 0; var < mainwindow->map->i->item1leftcount; ++var) {
    //     int i, j;
    //     outfile >> i;
    //     outfile >> j;
    //     QPoint *p = new QPoint(i ,j);
    //     mainwindow->map->i->item1LeftPositions.push_back(p);
    // }
    // for (int var = 0; var < mainwindow->map->i->item1rightcount; ++var) {
    //     int i, j;
    //     outfile >> i;
    //     outfile >> j;
    //     QPoint *p = new QPoint(i ,j);
    //     mainwindow->map->i->item1RightPositions.push_back(p);
    // }
    // for (int var = 0; var < mainwindow->map->buttons.size(); ++var) {
    //     outfile >> mainwindow->map->buttons[var]->IS_DIG_UP;
    //     outfile >> mainwindow->map->buttons[var]->IS_DIG_DOWN;
    //     outfile >> mainwindow->map->buttons[var]->IS_DIG_RIGHT;
    //     outfile >> mainwindow->map->buttons[var]->IS_DIG_LEFT;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_UP_1;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_UP_2;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_DOWN_1;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_DOWN_2;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_LEFT_1;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_LEFT_2;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_RIGHT_1;
    //     outfile >> mainwindow->map->buttons[var]->IS_CUT_RIGHT_2;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_UP;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_DOWN;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_RIGHT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_LEFT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_UPRIGHT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_UPLEFT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_DOWNRIGHT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_DOWNLEFT;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_RIGHTUP;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_RIGHTDOWN;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_LEFTUP;
    //     outfile >> mainwindow->map->buttons[var]->IS_PASS_LEFTDOWN;
    //     outfile >> mainwindow->map->buttons[var]->IS_RUBBISH;
    // }
    mainwindow->map->mapupdate();
    mainwindow->show();
    close();
}

OpenWidget::OpenWidget(QWidget *parent)
    : QWidget{parent}
{
    QPushButton *btn1 = new QPushButton("开始游戏", this);
    QPushButton *btn2 = new QPushButton("退出游戏", this);
    QPushButton *btn3 = new QPushButton("读取存档", this);
    QFont font1 = btn1->font();
    QFont font2 = btn2->font();
    QFont font3 = btn3->font();
    font1.setPointSize(30);
    font2.setPointSize(30);
    font3.setPointSize(30);
    btn1->setFont(font1);
    btn2->setFont(font2);
    btn3->setFont(font3);
    btn1->resize(200, 70);
    btn2->resize(200, 70);
    btn3->resize(200, 70);
    btn1->move(500, 400);
    btn3->move(500, 500);
    btn2->move(500, 600);
    connect(btn2, &QPushButton::clicked, this, &OpenWidget::exit);
    connect(btn1, &QPushButton::clicked, this, &OpenWidget::start);
    connect(btn3, &QPushButton::clicked, this, &OpenWidget::readsave);
}
