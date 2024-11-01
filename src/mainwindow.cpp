#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), receiveditem1(0), receiveditem2(0), receiveditem1left(0), receiveditem1right(0)
    , ui(new Ui::MainWindow), t_1(2000), t_2(50), t_3(500), coinnum(1000), value(1)
{
    ui->setupUi(this);
    map = new Map(this);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);
    layout->addWidget(map);
    map->i->raise();
    connect(ui->actiondigright, &QAction::triggered, this, &MainWindow::is_dig_right_state);
    connect(ui->actiondigleft, &QAction::triggered, this, &MainWindow::is_dig_left_state);
    connect(ui->actiondigup, &QAction::triggered, this, &MainWindow::is_dig_up_state);
    connect(ui->actiondigdown, &QAction::triggered, this, &MainWindow::is_dig_down_state);
    connect(ui->actioncutright, &QAction::triggered, this, &MainWindow::is_cut_right_state);
    connect(ui->actioncutleft, &QAction::triggered, this, &MainWindow::is_cut_left_state);
    connect(ui->actioncutup, &QAction::triggered, this, &MainWindow::is_cut_up_state);
    connect(ui->actioncutdown, &QAction::triggered, this, &MainWindow::is_cut_down_state);
    connect(ui->actionright, &QAction::triggered, this, &MainWindow::is_pass_right_state);
    connect(ui->actionleft, &QAction::triggered, this, &MainWindow::is_pass_left_state);
    connect(ui->actionup, &QAction::triggered, this, &MainWindow::is_pass_up_state);
    connect(ui->actiondown, &QAction::triggered, this, &MainWindow::is_pass_down_state);
    connect(ui->actionrightup, &QAction::triggered, this, &MainWindow::is_pass_rightup_state);
    connect(ui->actionupleft, &QAction::triggered, this, &MainWindow::is_pass_upleft_state);
    connect(ui->actionleftdown, &QAction::triggered, this, &MainWindow::is_pass_leftdown_state);
    connect(ui->actiondownright, &QAction::triggered, this, &MainWindow::is_pass_downright_state);
    connect(ui->actionrightdown, &QAction::triggered, this, &MainWindow::is_pass_rightdown_state);
    connect(ui->actiondownleft, &QAction::triggered, this, &MainWindow::is_pass_downleft_state);
    connect(ui->actionleftup, &QAction::triggered, this, &MainWindow::is_pass_leftup_state);
    connect(ui->actionupright, &QAction::triggered, this, &MainWindow::is_pass_upright_state);
    connect(ui->actionrubbish, &QAction::triggered, this, &MainWindow::is_rubbish_state);
    connect(ui->actionsave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actiondigv, &QAction::triggered, this, &MainWindow::levelup1);
    connect(ui->actionpassv, &QAction::triggered, this, &MainWindow::levelup2);
    connect(ui->actioncutv, &QAction::triggered, this, &MainWindow::levelup3);
    connect(ui->actioncenterbig, &QAction::triggered, this, &MainWindow::levelup4);
    connect(ui->actionraisecoin, &QAction::triggered, this, &MainWindow::levelup5);
    for (int var = 0; var < map->buttons.size(); ++var) {
        connect(map->buttons[var] ,&MapPushButton::clk, this, &MainWindow::put);
        connect(map->buttons[var] ,&MapPushButton::remove, this, &MainWindow::Remove);
    }
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);

    connect(timer1, &QTimer::timeout, this, &MainWindow::generate);
    connect(timer2, &QTimer::timeout, this, &MainWindow::updatePosition);
    connect(timer2, &QTimer::timeout, this, &MainWindow::cutupdatePosition);
    connect(timer2, &QTimer::timeout, this, &MainWindow::numupdate);
    connect(timer3, &QTimer::timeout, this, &MainWindow::cutgenerate);

    timer1->start(t_1);
    timer2->start(t_2);
    timer3->start(t_3);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numupdate()
{
    QString a1("物品1的数量：");
    QString b1 = QString::number(receiveditem1);
    map->i->label1->setText(a1+b1);
    QString a2("物品2的数量：");
    QString b2 = QString::number(receiveditem2);
    map->i->label2->setText(a2+b2);
    QString a3("物品1左的数量：");
    QString b3 = QString::number(receiveditem1left);
    map->i->label3->setText(a3+b3);
    QString a4("物品1右的数量：");
    QString b4 = QString::number(receiveditem1right);
    map->i->label4->setText(a4+b4);
    QString a5("金币的数量：");
    QString b5 = QString::number(coinnum);
    map->i->label5->setText(a5+b5);
}

void MainWindow::save() {
    std::fstream outfile("C:/Users/72802/Desktop/project/ShapeZ/memory");
    // int item1count;
    // int item2count;
    // int item1rightcount;
    // int item1leftcount;
    // QVector<QPoint *> item1Positions;
    // QVector<QPoint *> item2Positions;
    // QVector<QPoint *> item1RightPositions;
    // QVector<QPoint *> item1LeftPositions;
    // int receiveditem1;
    // int receiveditem2;
    // int receiveditem1left;
    // int receiveditem1right;
    //QVector<MapPushButton *> buttons;
    QString filename = QFileDialog::getSaveFileName(this, "save", QDir::homePath(), "Text Files (*.txt);;All Files (*.*)");
    if(!filename.isEmpty()) {
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly)) {
            QTextStream outfile(&file);
            outfile << map->i->item1count << " " << map->i->item2count << " "
                    << map->i->item1rightcount << " " << map->i->item1leftcount << " " << receiveditem1
                    << " " << receiveditem2 << " " << receiveditem1left << " " << receiveditem1right
                    << " " << t_1 << " " << t_2 << " " << t_3 << " " << coinnum << " " <<
                value << " " << map->center_imin << " " << map->center_jmin << " " << map->length << " ";
            for (int var = 0; var < map->i->item1count; ++var) {
                outfile << map->i->item1Positions[var]->x();
                outfile << " ";
                outfile << map->i->item1Positions[var]->y();
                outfile << " ";
            }
            for (int var = 0; var < map->i->item2count; ++var) {
                outfile << map->i->item2Positions[var]->x();
                outfile<<" ";
                outfile << map->i->item2Positions[var]->y();
                outfile<<" ";
            }
            for (int var = 0; var < map->i->item1leftcount; ++var) {
                outfile << map->i->item1LeftPositions[var]->x();
                outfile<<" ";
                outfile << map->i->item1LeftPositions[var]->y();
                outfile<<" ";
            }
            for (int var = 0; var < map->i->item1rightcount; ++var) {
                outfile << map->i->item1RightPositions[var]->x();
                outfile<<" ";
                outfile << map->i->item1RightPositions[var]->y();
                outfile<<" ";
            }
            for (int var = 0; var < map->buttons.size(); ++var) {
                outfile << map->buttons[var]->IS_DIG_UP;
                outfile<<" ";
                outfile << map->buttons[var]->IS_DIG_DOWN;
                outfile<<" ";
                outfile << map->buttons[var]->IS_DIG_RIGHT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_DIG_LEFT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_UP_1;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_UP_2;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_DOWN_1;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_DOWN_2;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_LEFT_1;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_LEFT_2;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_RIGHT_1;
                outfile<<" ";
                outfile << map->buttons[var]->IS_CUT_RIGHT_2;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_UP;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_DOWN;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_RIGHT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_LEFT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_UPRIGHT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_UPLEFT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_DOWNRIGHT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_DOWNLEFT;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_RIGHTUP;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_RIGHTDOWN;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_LEFTUP;
                outfile<<" ";
                outfile << map->buttons[var]->IS_PASS_LEFTDOWN;
                outfile<<" ";
                outfile << map->buttons[var]->IS_RUBBISH;
                outfile<<" ";
            }
            file.close();
        }
    }
    // outfile << map->i->item1count << " " << map->i->item2count << " "
    //         << map->i->item1rightcount << " " << map->i->item1leftcount << " " << receiveditem1
    //         << " " << receiveditem2 << " " << receiveditem1left << " " << receiveditem1right
    //         << " " << t_1 << " " << t_2 << " " << t_3 << " " << coinnum << " " <<
    //     value << " " << map->center_imin << " " << map->center_jmin << " " << map->length << std::endl;
    // for (int var = 0; var < map->i->item1count; ++var) {
    //     outfile << map->i->item1Positions[var]->x();
    //     outfile << std::endl;
    //     outfile << map->i->item1Positions[var]->y();
    //     outfile << std::endl;
    // }
    // for (int var = 0; var < map->i->item2count; ++var) {
    //     outfile << map->i->item2Positions[var]->x();
    //     outfile<<std::endl;
    //     outfile << map->i->item2Positions[var]->y();
    //     outfile<<std::endl;
    // }
    // for (int var = 0; var < map->i->item1leftcount; ++var) {
    //     outfile << map->i->item1LeftPositions[var]->x();
    //     outfile<<std::endl;
    //     outfile << map->i->item1LeftPositions[var]->y();
    //     outfile<<std::endl;
    // }
    // for (int var = 0; var < map->i->item1rightcount; ++var) {
    //     outfile << map->i->item1RightPositions[var]->x();
    //     outfile<<std::endl;
    //     outfile << map->i->item1RightPositions[var]->y();
    //     outfile<<std::endl;
    // }
    // for (int var = 0; var < map->buttons.size(); ++var) {
    //     outfile << map->buttons[var]->IS_DIG_UP;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_DIG_DOWN;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_DIG_RIGHT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_DIG_LEFT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_UP_1;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_UP_2;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_DOWN_1;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_DOWN_2;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_LEFT_1;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_LEFT_2;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_RIGHT_1;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_CUT_RIGHT_2;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_UP;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_DOWN;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_RIGHT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_LEFT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_UPRIGHT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_UPLEFT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_DOWNRIGHT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_DOWNLEFT;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_RIGHTUP;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_RIGHTDOWN;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_LEFTUP;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_PASS_LEFTDOWN;
    //     outfile<<std::endl;
    //     outfile << map->buttons[var]->IS_RUBBISH;
    //     outfile<<std::endl;
    // }
    // outfile.close();
}

void MainWindow::is_dig_right_state() {
    IS_DIG_RIGHT_STATE = true;
}

void MainWindow::is_dig_left_state() {
    IS_DIG_LEFT_STATE = true;
}
void MainWindow::is_dig_up_state() {
    IS_DIG_UP_STATE = true;
}
void MainWindow::is_dig_down_state() {
    IS_DIG_DOWN_STATE = true;
}

void MainWindow::is_cut_up_state() {
    IS_CUT_UP_STATE = true;
}
void MainWindow::is_cut_down_state() {
    IS_CUT_DOWN_STATE = true;
}
void MainWindow::is_cut_right_state() {
    IS_CUT_RIGHT_STATE = true;
}
void MainWindow::is_cut_left_state() {
    IS_CUT_LEFT_STATE = true;
}
void MainWindow::is_pass_right_state() {
    IS_PASS_RIGHT_STATE = true;
}
void MainWindow::is_pass_left_state() {
    IS_PASS_LEFT_STATE = true;
}
void MainWindow::is_pass_up_state() {
    IS_PASS_UP_STATE = true;
}
void MainWindow::is_pass_down_state() {
    IS_PASS_DOWN_STATE = true;
}
void MainWindow::is_pass_rightup_state() {
    IS_PASS_RIGHTUP_STATE = true;
}
void MainWindow::is_pass_upleft_state() {
    IS_PASS_UPLEFT_STATE = true;
}
void MainWindow::is_pass_leftdown_state() {
    IS_PASS_LEFTDOWN_STATE = true;
}
void MainWindow::is_pass_downright_state() {
    IS_PASS_DOWNRIGHT_STATE = true;
}
void MainWindow::is_pass_rightdown_state() {
    IS_PASS_RIGHTDOWN_STATE = true;
}
void MainWindow::is_pass_downleft_state() {
    IS_PASS_DOWNLEFT_STATE = true;
}
void MainWindow::is_pass_leftup_state() {
    IS_PASS_LEFTUP_STATE = true;
}
void MainWindow::is_pass_upright_state() {
    IS_PASS_UPRIGHT_STATE = true;
}
void MainWindow::is_rubbish_state() {
    IS_RUBBISH_STATE = true;
}

void MainWindow::put(int x, int y) {
    if(IS_DIG_RIGHT_STATE) {
        if(x >= 160 && x <= 320 && y >= 520 && y <= 680){
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digright2.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_RIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_RIGHT = true;
        } else if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        } else if(x >= 920 && x <= 1080 && y >= 80 && y <= 240) {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digright3.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_RIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_RIGHT = true;
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digright1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_RIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_RIGHT = true;
        }
    }//图标变成采矿器（右）
    if(IS_DIG_LEFT_STATE) {
        if(x >= 160 && x <= 320 && y >= 520 && y <= 680){
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digleft2.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_LEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_LEFT = true;
        } else if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        } else if(x >= 920 && x <= 1080 && y >= 80 && y <= 240) {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digleft3.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_LEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_LEFT = true;
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digleft1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_LEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_LEFT = true;
        }
    }//图标变成采矿器（左）
    if(IS_DIG_UP_STATE) {
        if(x >= 160 && x <= 320 && y >= 520 && y <= 680){
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digup2.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_UP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_UP = true;
        } else if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        } else if(x >= 920 && x <= 1080 && y >= 80 && y <= 240) {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digup3.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_UP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_UP = true;
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digup1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_UP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_UP = true;
        }
    }//图标变成采矿器（上）
    if(IS_DIG_DOWN_STATE) {
        if(x >= 160 && x <= 320 && y >= 520 && y <= 680){
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digdown2.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_DOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_DOWN = true;
        } else if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        } else if(x >= 920 && x <= 1080 && y >= 80 && y <= 240) {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digdown3.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_DOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_DOWN = true;
            qDebug() << "1";
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/digdown1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_DIG_DOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_DIG_DOWN = true;
        }
    }//图标变成采矿器（下）
    if(IS_CUT_UP_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440){
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/cutup1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            map->buttons[30 * (y/40) + x/40 + 1]->setIcon(QIcon(":/map/cutup2.png"));
            IS_CUT_UP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40 + 1]->init();
            map->buttons[30 * (y/40) + x/40]->IS_CUT_UP_1 = true;
            map->buttons[30 * (y/40) + x/40 + 1]->IS_CUT_UP_2 = true;
        }
    }//图标变成切割机（上）
    if(IS_CUT_DOWN_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440){
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/cutdown1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            map->buttons[30 * (y/40) + x/40 - 1]->setIcon(QIcon(":/map/cutdown2.png"));
            IS_CUT_DOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40 - 1]->init();
            map->buttons[30 * (y/40) + x/40]->IS_CUT_DOWN_1 = true;
            map->buttons[30 * (y/40) + x/40 - 1]->IS_CUT_DOWN_2 = true;
        }
    }//图标变成切割机（下）
    if(IS_CUT_LEFT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440){
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/cutleft1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            map->buttons[30 * (y/40) + x/40 - 30]->setIcon(QIcon(":/map/cutleft2.png"));
            IS_CUT_LEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40 - 30]->init();
            map->buttons[30 * (y/40) + x/40]->IS_CUT_LEFT_1 = true;
            map->buttons[30 * (y/40) + x/40 - 30]->IS_CUT_LEFT_2 = true;
        }
    }//图标变成切割机（左）
    if(IS_CUT_RIGHT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440){
        } else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/cutright1.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            map->buttons[30 * (y/40) + x/40 + 30]->setIcon(QIcon(":/map/cutright2.png"));
            IS_CUT_RIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40 + 30]->init();
            map->buttons[30 * (y/40) + x/40]->IS_CUT_RIGHT_1 = true;
            map->buttons[30 * (y/40) + x/40 + 30]->IS_CUT_RIGHT_2 = true;
        }
    }//图标变成切割机（右）
    if(IS_PASS_RIGHT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passright.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_RIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHT = true;
        }
    }//图标变成传送带（右）
    if(IS_PASS_LEFT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passleft.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_LEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFT = true;
        }
    }//图标变成传送带（左）
    if(IS_PASS_UP_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passup.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_UP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_UP = true;
        }
    }//图标变成传送带（上）
    if(IS_PASS_DOWN_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passdown.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_DOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWN = true;
        }
    }//图标变成传送带（下）
    if(IS_PASS_RIGHTDOWN_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passrightdown.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_RIGHTDOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTDOWN = true;
        }
    }//图标变成传送带（右下）
    if(IS_PASS_DOWNLEFT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passdownleft.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_DOWNLEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNLEFT = true;
        }
    }//图标变成传送带（下左）
    if(IS_PASS_LEFTUP_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passleftup.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_LEFTUP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTUP = true;
        }
    }//图标变成传送带（左上）
    if(IS_PASS_UPRIGHT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passupright.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_UPRIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_UPRIGHT = true;
        }
    }//图标变成传送带（上右）
    if(IS_PASS_RIGHTUP_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passrightup.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_RIGHTUP_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTUP = true;
        }
    }//图标变成传送带（右上）
    if(IS_PASS_UPLEFT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passupleft.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_UPLEFT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_UPLEFT = true;
        }
    }//图标变成传送带（上左）
    if(IS_PASS_LEFTDOWN_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passleftdown.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_LEFTDOWN_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTDOWN = true;
        }
    }//图标变成传送带（左下）
    if(IS_PASS_DOWNRIGHT_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/passdownright.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_PASS_DOWNRIGHT_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNRIGHT = true;
        }
    }//图标变成传送带（下右）
    if(IS_RUBBISH_STATE) {
        if(x >= 520 && x <= 640 && y >= 320 && y <= 440) {
        }
        else {
            map->buttons[30 * (y/40) + x/40]->setIcon(QIcon(":/map/rubbish.png"));
            map->buttons[30 * (y/40) + x/40]->setIconSize(QSize(40, 40));
            IS_RUBBISH_STATE = false;
            map->buttons[30 * (y/40) + x/40]->init();
            map->buttons[30 * (y/40) + x/40]->IS_RUBBISH = true;
        }
    }//图标变成垃圾桶
}

void MainWindow::Remove(int x, int y) {
    int i = x/40;
    int j = y/40;
    if(map->buttons[30 * j + i]->IS_CUT_UP_1) {
        map->buttons[30 * j + i]->init();
        map->buttons[30 * j + i + 1]->init();
        if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 1]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i + 1]->setIconSize(QSize(40, 40));
        } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
        } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 1]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i + 1]->setIconSize(QSize(40, 40));
        } else {
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 1]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i + 1]->setIconSize(QSize(40, 40));
            qDebug() << "0";
        }
    }
    if(map->buttons[30 * j + i]->IS_CUT_DOWN_1) {
        map->buttons[30 * j + i - 1]->init();
        if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 1]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i - 1]->setIconSize(QSize(40, 40));
        } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
        } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 1]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i - 1]->setIconSize(QSize(40, 40));
        } else {
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 1]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i - 1]->setIconSize(QSize(40, 40));
        }
    }
    if(map->buttons[30 * j + i]->IS_CUT_RIGHT_1) {
        map->buttons[30 * j + i + 30]->init();
        if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 30]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i + 30]->setIconSize(QSize(40, 40));
        } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
        } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 30]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i + 30]->setIconSize(QSize(40, 40));
        } else {
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i + 30]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i + 30]->setIconSize(QSize(40, 40));
        }
    }
    if(map->buttons[30 * j + i]->IS_CUT_LEFT_1) {
        map->buttons[30 * j + i - 30]->init();
        if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 30]->setIcon(QIcon(":/map/map2.png"));
            map->buttons[30 * j + i - 30]->setIconSize(QSize(40, 40));
        } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
        } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 30]->setIcon(QIcon(":/map/map4.png"));
            map->buttons[30 * j + i - 30]->setIconSize(QSize(40, 40));
        } else {
            map->buttons[30 * j + i]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
            map->buttons[30 * j + i - 30]->setIcon(QIcon(":/map/map1.png"));
            map->buttons[30 * j + i - 30]->setIconSize(QSize(40, 40));
        }
    } else{
        map->buttons[30 * j + i]->init();
    if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
        map->buttons[30 * j + i]->setIcon(QIcon(":/map/map2.png"));
        map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
    } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
    } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
        map->buttons[30 * j + i]->setIcon(QIcon(":/map/map4.png"));
        map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
    } else {
        map->buttons[30 * j + i]->setIcon(QIcon(":/map/map1.png"));
        map->buttons[30 * j + i]->setIconSize(QSize(40, 40));
    }
    }
}

void MainWindow::generate() {
    for (int i = 160; i <= 320; i+=40) {
        for (int j = 520; j <= 680; j+=40) {
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_UP && (map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UP || map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UPRIGHT || map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UPLEFT)) {
                if(map->i->item1count == 0 || map->i->item1Positions[map->i->item1count - 1]->y() != j - 10) {
                    map->i->item1count++;
                    QPoint *p = new QPoint(i + 10, j - 10);
                    map->i->item1Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_DOWN && (map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWN || map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWNRIGHT || map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWNLEFT)) {
                if(map->i->item1count == 0 || map->i->item1Positions[map->i->item1count - 1]->y() != j + 30) {
                    map->i->item1count++;
                    QPoint *p = new QPoint(i + 10, j + 30);
                    map->i->item1Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_RIGHT && (map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHT || map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHTUP || map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHTDOWN)) {
                if(map->i->item1count == 0 || map->i->item1Positions[map->i->item1count - 1]->x() != i + 30) {
                    map->i->item1count++;
                    QPoint *p = new QPoint(i + 30, j + 10);
                    map->i->item1Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_LEFT && (map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFT || map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFTUP || map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFTDOWN)) {
                if(map->i->item1count == 0 || map->i->item1Positions[map->i->item1count - 1]->x() != i - 10) {
                    map->i->item1count++;
                    QPoint *p = new QPoint(i - 10, j + 10);
                    map->i->item1Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
        }
    }
    for (int i = 920; i <= 1080; i+=40) {
        for (int j = 80; j <= 240; j+=40) {
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_UP && (map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UP || map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UPRIGHT || map->buttons[30 * (j/40 - 1) + i/40]->IS_PASS_UPLEFT)) {
                if(map->i->item2count == 0 || map->i->item2Positions[map->i->item2count - 1]->y() != j - 10) {
                    map->i->item2count++;
                    QPoint *p = new QPoint(i + 10, j - 10);
                    map->i->item2Positions.push_back(p);
                    map->i->update();
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_DOWN && (map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWN || map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWNRIGHT || map->buttons[30 * (j/40 + 1) + i/40]->IS_PASS_DOWNLEFT)) {
                if(map->i->item2count == 0 || map->i->item2Positions[map->i->item2count - 1]->y() != j + 30) {
                    map->i->item2count++;
                    QPoint *p = new QPoint(i + 10, j + 30);
                    map->i->item2Positions.push_back(p);
                    map->i->update();
                    qDebug() << map->i->item2count;
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_RIGHT && (map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHT || map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHTUP || map->buttons[30 * j/40 + i/40 + 1]->IS_PASS_RIGHTDOWN)) {
                if(map->i->item2count == 0 || map->i->item2Positions[map->i->item2count - 1]->x() != i + 30) {
                    map->i->item2count++;
                    QPoint *p = new QPoint(i + 30, j + 10);
                    map->i->item2Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
            if(map->buttons[30 * (j/40) + i/40]->IS_DIG_LEFT && (map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFT || map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFTUP || map->buttons[30 * j/40 + i/40 - 1]->IS_PASS_LEFTDOWN)) {
                if(map->i->item2count == 0 || map->i->item2Positions[map->i->item2count - 1]->x() != i - 10) {
                    map->i->item2count++;
                    QPoint *p = new QPoint(i - 10, j + 10);
                    map->i->item2Positions.push_back(p);
                    map->i->update();
                    //qDebug() << "0";
                }
            }
        }
    }
}
void MainWindow::updatePosition() {
    for (int var = 0; var < map->i->item1count; ++var) {
        int x = map->i->item1Positions[var]->x() + 10;
        int y = map->i->item1Positions[var]->y() + 10;
        if(map->buttons[30 * (y/40) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40 - 1) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40) + x / 40 - 1]->IS_RUBBISH) {
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            break;
        }
        if(x >= map->center_imin && x <= map->center_imin + map->length && y >= map->center_jmin && y <= map->center_jmin + map->length) {
            receiveditem1++;
            coinnum += value;
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            qDebug() << receiveditem1;
            break;
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UP || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UP)) {
            if(var == 0 || (map->i->item1Positions[var - 1]->y() < map->i->item1Positions[var]->y() - 24) || map->i->item1Positions[var - 1]->x() != map->i->item1Positions[var]->x()){
            map->i->item1Positions[var]->ry() -= 4;
            map->i->update();
            //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWN) {
            if(var == 0 || (map->i->item1Positions[var - 1]->y() > map->i->item1Positions[var]->y() + 24) || map->i->item1Positions[var - 1]->x() != map->i->item1Positions[var]->x()){
                map->i->item1Positions[var]->ry() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHT) {
            if(var == 0 || (map->i->item1Positions[var - 1]->x() > map->i->item1Positions[var]->x() + 24) || map->i->item1Positions[var - 1]->y() != map->i->item1Positions[var]->y()){
                map->i->item1Positions[var]->rx() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFT || (x%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFT)) {
            if(var == 0 || (map->i->item1Positions[var - 1]->x() < map->i->item1Positions[var]->x() - 24) || map->i->item1Positions[var - 1]->y() != map->i->item1Positions[var]->y()){
                map->i->item1Positions[var]->rx() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() > map->i->item1Positions[var]->x() + 24) || map->i->item1Positions[var - 1]->y() < map->i->item1Positions[var]->y() - 24) {
                map->i->item1Positions[var]->ry() -= 2;
                map->i->item1Positions[var]->rx() += 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 10) {
                map->i->item1Positions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPLEFT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() < map->i->item1Positions[var]->x() - 24) || map->i->item1Positions[var - 1]->y() < map->i->item1Positions[var]->y() - 24) {
                map->i->item1Positions[var]->ry() -= 2;
                map->i->item1Positions[var]->rx() -= 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 10) {
                map->i->item1Positions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNLEFT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() < map->i->item1Positions[var]->x() - 24) || map->i->item1Positions[var - 1]->y() > map->i->item1Positions[var]->y() + 24) {
                map->i->item1Positions[var]->ry() += 2;
                map->i->item1Positions[var]->rx() -= 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 10) {
                map->i->item1Positions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() > map->i->item1Positions[var]->x() + 24) || map->i->item1Positions[var - 1]->y() > map->i->item1Positions[var]->y() + 24) {
                map->i->item1Positions[var]->ry() += 2;
                map->i->item1Positions[var]->rx() += 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 10) {
                map->i->item1Positions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTUP) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() > map->i->item1Positions[var]->x() + 24) || map->i->item1Positions[var - 1]->y() < map->i->item1Positions[var]->y() - 24) {
                map->i->item1Positions[var]->ry() -= 2;
                map->i->item1Positions[var]->rx() += 2;
            }
            if(map->i->item1Positions[var]->x() == x0 + 10) {
                map->i->item1Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTDOWN) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() > map->i->item1Positions[var]->x() + 24) || map->i->item1Positions[var - 1]->y() > map->i->item1Positions[var]->y() + 24) {
                map->i->item1Positions[var]->ry() += 2;
                map->i->item1Positions[var]->rx() += 2;
            }
            if(map->i->item1Positions[var]->x() == x0 + 10) {
                map->i->item1Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTUP || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() < map->i->item1Positions[var]->x() - 24) || map->i->item1Positions[var - 1]->y() < map->i->item1Positions[var]->y() - 24) {
                map->i->item1Positions[var]->ry() -= 2;
                map->i->item1Positions[var]->rx() -= 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 30) {
                map->i->item1Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTDOWN || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1Positions[var - 1]->x() < map->i->item1Positions[var]->x() - 24) || map->i->item1Positions[var - 1]->y() > map->i->item1Positions[var]->y() + 24) {
                map->i->item1Positions[var]->ry() += 2;
                map->i->item1Positions[var]->rx() -= 2;
            }
            if(map->i->item1Positions[var]->x() == x0 - 30) {
                map->i->item1Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
    }
    for (int var = 0; var < map->i->item2count; ++var) {
        int x = map->i->item2Positions[var]->x() + 10;
        int y = map->i->item2Positions[var]->y() + 10;
        if(map->buttons[30 * (y/40) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40 - 1) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40) + x / 40 - 1]->IS_RUBBISH) {
            map->i->item2Positions.erase(map->i->item2Positions.begin() + var);
            var--;
            map->i->item2count--;
            map->i->update();
            break;
        }
        if(x >= map->center_imin && x <= map->center_imin + map->length && y >= map->center_jmin - 10 && y <= map->center_jmin + map->length) {
            receiveditem2++;
            coinnum += value;
            map->i->item2Positions.erase(map->i->item2Positions.begin() + var);
            var--;
            map->i->item2count--;
            map->i->update();
            qDebug() << receiveditem2;
            break;
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UP || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UP)) {
            if(var == 0 || (map->i->item2Positions[var - 1]->y() < map->i->item2Positions[var]->y() - 24) || map->i->item2Positions[var - 1]->x() != map->i->item2Positions[var]->x()){
                map->i->item2Positions[var]->ry() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWN) {
            if(var == 0 || (map->i->item2Positions[var - 1]->y() > map->i->item2Positions[var]->y() + 24) || map->i->item2Positions[var - 1]->x() != map->i->item2Positions[var]->x()){
                map->i->item2Positions[var]->ry() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHT) {
            if(var == 0 || (map->i->item2Positions[var - 1]->x() > map->i->item2Positions[var]->x() + 24) || map->i->item2Positions[var - 1]->y() != map->i->item2Positions[var]->y()){
                map->i->item2Positions[var]->rx() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFT || (x%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFT)) {
            if(var == 0 || (map->i->item2Positions[var - 1]->x() < map->i->item2Positions[var]->x() - 24) || map->i->item2Positions[var - 1]->y() != map->i->item2Positions[var]->y()){
                map->i->item2Positions[var]->rx() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() > map->i->item2Positions[var]->x() + 24) || map->i->item2Positions[var - 1]->y() < map->i->item2Positions[var]->y() - 24) {
                map->i->item2Positions[var]->ry() -= 2;
                map->i->item2Positions[var]->rx() += 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 10) {
                map->i->item2Positions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPLEFT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() < map->i->item2Positions[var]->x() - 24) || map->i->item2Positions[var - 1]->y() < map->i->item2Positions[var]->y() - 24) {
                map->i->item2Positions[var]->ry() -= 2;
                map->i->item2Positions[var]->rx() -= 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 10) {
                map->i->item2Positions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNLEFT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_DOWNLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() < map->i->item2Positions[var]->x() - 24) || map->i->item2Positions[var - 1]->y() > map->i->item2Positions[var]->y() + 24) {
                map->i->item2Positions[var]->ry() += 2;
                map->i->item2Positions[var]->rx() -= 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 10) {
                map->i->item2Positions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_DOWNRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() > map->i->item2Positions[var]->x() + 24) || map->i->item2Positions[var - 1]->y() > map->i->item2Positions[var]->y() + 24) {
                map->i->item2Positions[var]->ry() += 2;
                map->i->item2Positions[var]->rx() += 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 10) {
                map->i->item2Positions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTUP) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() > map->i->item2Positions[var]->x() + 24) || map->i->item2Positions[var - 1]->y() < map->i->item2Positions[var]->y() - 24) {
                map->i->item2Positions[var]->ry() -= 2;
                map->i->item2Positions[var]->rx() += 2;
            }
            if(map->i->item2Positions[var]->x() == x0 + 10) {
                map->i->item2Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTDOWN) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() > map->i->item2Positions[var]->x() + 24) || map->i->item2Positions[var - 1]->y() > map->i->item2Positions[var]->y() + 24) {
                map->i->item2Positions[var]->ry() += 2;
                map->i->item2Positions[var]->rx() += 2;
            }
            if(map->i->item2Positions[var]->x() == x0 + 10) {
                map->i->item2Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTUP || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() < map->i->item2Positions[var]->x() - 24) || map->i->item2Positions[var - 1]->y() < map->i->item2Positions[var]->y() - 24) {
                map->i->item2Positions[var]->ry() -= 2;
                map->i->item2Positions[var]->rx() -= 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 30) {
                map->i->item2Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTDOWN || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item2Positions[var - 1]->x() < map->i->item2Positions[var]->x() - 24) || map->i->item2Positions[var - 1]->y() > map->i->item2Positions[var]->y() + 24) {
                map->i->item2Positions[var]->ry() += 2;
                map->i->item2Positions[var]->rx() -= 2;
            }
            if(map->i->item2Positions[var]->x() == x0 - 30) {
                map->i->item2Positions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
    }
}

void MainWindow::cutgenerate() {
    for (int var = 0; var < map->i->item1count; ++var) {
        int x = map->i->item1Positions[var]->x() + 10;
        int y = map->i->item1Positions[var]->y() + 10;
        //qDebug() << "1";
        if(map->buttons[30 * (y/40 - 1) + x/40]->IS_CUT_UP_1) {
            map->i->item1rightcount++;
            map->i->item1leftcount++;
            QPoint *p1 = new QPoint(x - 10, y - 90);
            QPoint *p2 = new QPoint(x + 30, y - 90);
            map->i->item1RightPositions.push_back(p2);
            map->i->item1LeftPositions.push_back(p1);
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            qDebug() << "1";
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_CUT_DOWN_1) {
            map->i->item1rightcount++;
            map->i->item1leftcount++;
            QPoint *p1 = new QPoint(x - 10, y + 30);
            QPoint *p2 = new QPoint(x - 50, y + 30);
            map->i->item1RightPositions.push_back(p2);
            map->i->item1LeftPositions.push_back(p1);
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            qDebug() << "1";
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_CUT_RIGHT_1) {
            map->i->item1rightcount++;
            map->i->item1leftcount++;
            QPoint *p1 = new QPoint(x + 30, y - 10);
            QPoint *p2 = new QPoint(x + 30, y + 30);
            map->i->item1RightPositions.push_back(p2);
            map->i->item1LeftPositions.push_back(p1);
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            qDebug() << "1";
        }
        if(map->buttons[30 * (y/40) + x/40 - 1]->IS_CUT_LEFT_1) {
            map->i->item1rightcount++;
            map->i->item1leftcount++;
            QPoint *p1 = new QPoint(x - 90, y - 10);
            QPoint *p2 = new QPoint(x - 90, y - 50);
            map->i->item1RightPositions.push_back(p2);
            map->i->item1LeftPositions.push_back(p1);
            map->i->item1Positions.erase(map->i->item1Positions.begin() + var);
            var--;
            map->i->item1count--;
            map->i->update();
            qDebug() << "1";
        }
    }
}

void MainWindow::cutupdatePosition() {
    for (int var = 0; var < map->i->item1rightcount; ++var) {
        int x = map->i->item1RightPositions[var]->x() + 10;
        int y = map->i->item1RightPositions[var]->y() + 10;
        if(map->buttons[30 * (y/40) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40 - 1) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40) + x / 40 - 1]->IS_RUBBISH) {
            map->i->item1RightPositions.erase(map->i->item1RightPositions.begin() + var);
            var--;
            map->i->item1rightcount--;
            map->i->update();
            break;
        }
        if(x >= map->center_imin && x <= map->center_imin + map->length && y >= map->center_jmin && y <= map->center_jmin + map->length) {
            receiveditem1right++;
            coinnum += value;
            map->i->item1RightPositions.erase(map->i->item1RightPositions.begin() + var);
            var--;
            map->i->item1rightcount--;
            map->i->update();
            qDebug() << receiveditem1right;
            break;
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UP || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UP)) {
            if(var == 0 || (map->i->item1RightPositions[var - 1]->y() < map->i->item1RightPositions[var]->y() - 24) || map->i->item1RightPositions[var - 1]->x() != map->i->item1RightPositions[var]->x()){
                map->i->item1RightPositions[var]->ry() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWN) {
            if(var == 0 || (map->i->item1RightPositions[var - 1]->y() > map->i->item1RightPositions[var]->y() + 24) || map->i->item1RightPositions[var - 1]->x() != map->i->item1RightPositions[var]->x()){
                map->i->item1RightPositions[var]->ry() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHT) {
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() > map->i->item1RightPositions[var]->x() + 24) || map->i->item1RightPositions[var - 1]->y() != map->i->item1RightPositions[var]->y()){
                map->i->item1RightPositions[var]->rx() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFT || (x%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFT)) {
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() < map->i->item1RightPositions[var]->x() - 24) || map->i->item1RightPositions[var - 1]->y() != map->i->item1RightPositions[var]->y()){
                map->i->item1RightPositions[var]->rx() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() > map->i->item1RightPositions[var]->x() + 24) || map->i->item1RightPositions[var - 1]->y() < map->i->item1RightPositions[var]->y() - 24) {
                map->i->item1RightPositions[var]->ry() -= 2;
                map->i->item1RightPositions[var]->rx() += 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 10) {
                map->i->item1RightPositions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPLEFT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() < map->i->item1RightPositions[var]->x() - 24) || map->i->item1RightPositions[var - 1]->y() < map->i->item1RightPositions[var]->y() - 24) {
                map->i->item1RightPositions[var]->ry() -= 2;
                map->i->item1RightPositions[var]->rx() -= 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 10) {
                map->i->item1RightPositions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNLEFT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() < map->i->item1RightPositions[var]->x() - 24) || map->i->item1RightPositions[var - 1]->y() > map->i->item1RightPositions[var]->y() + 24) {
                map->i->item1RightPositions[var]->ry() += 2;
                map->i->item1RightPositions[var]->rx() -= 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 10) {
                map->i->item1RightPositions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() > map->i->item1RightPositions[var]->x() + 24) || map->i->item1RightPositions[var - 1]->y() > map->i->item1RightPositions[var]->y() + 24) {
                map->i->item1RightPositions[var]->ry() += 2;
                map->i->item1RightPositions[var]->rx() += 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 10) {
                map->i->item1RightPositions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTUP) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() > map->i->item1RightPositions[var]->x() + 24) || map->i->item1RightPositions[var - 1]->y() < map->i->item1RightPositions[var]->y() - 24) {
                map->i->item1RightPositions[var]->ry() -= 2;
                map->i->item1RightPositions[var]->rx() += 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 + 10) {
                map->i->item1RightPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTDOWN) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() > map->i->item1RightPositions[var]->x() + 24) || map->i->item1RightPositions[var - 1]->y() > map->i->item1RightPositions[var]->y() + 24) {
                map->i->item1RightPositions[var]->ry() += 2;
                map->i->item1RightPositions[var]->rx() += 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 + 10) {
                map->i->item1RightPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTUP || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() < map->i->item1RightPositions[var]->x() - 24) || map->i->item1RightPositions[var - 1]->y() < map->i->item1RightPositions[var]->y() - 24) {
                map->i->item1RightPositions[var]->ry() -= 2;
                map->i->item1RightPositions[var]->rx() -= 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 30) {
                map->i->item1RightPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTDOWN || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1RightPositions[var - 1]->x() < map->i->item1RightPositions[var]->x() - 24) || map->i->item1RightPositions[var - 1]->y() > map->i->item1RightPositions[var]->y() + 24) {
                map->i->item1RightPositions[var]->ry() += 2;
                map->i->item1RightPositions[var]->rx() -= 2;
            }
            if(map->i->item1RightPositions[var]->x() == x0 - 30) {
                map->i->item1RightPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
    }
    for (int var = 0; var < map->i->item1leftcount; ++var) {
        int x = map->i->item1LeftPositions[var]->x() + 10;
        int y = map->i->item1LeftPositions[var]->y() + 10;
        if(map->buttons[30 * (y/40) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40 - 1) + x / 40]->IS_RUBBISH ||
            map->buttons[30 * (y/40) + x / 40 - 1]->IS_RUBBISH) {
            map->i->item1LeftPositions.erase(map->i->item1LeftPositions.begin() + var);
            var--;
            map->i->item1leftcount--;
            map->i->update();
            break;
        }
        if(x >= map->center_imin && x <= map->center_imin + map->length && y >= map->center_jmin && y <= map->center_jmin + map->length) {
            receiveditem1left++;
            coinnum += value;
            map->i->item1LeftPositions.erase(map->i->item1LeftPositions.begin() + var);
            var--;
            map->i->item1leftcount--;
            map->i->update();
            qDebug() << receiveditem1left;
            break;
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UP || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UP)) {
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->y() < map->i->item1LeftPositions[var]->y() - 24) || map->i->item1LeftPositions[var - 1]->x() != map->i->item1LeftPositions[var]->x()){
                map->i->item1LeftPositions[var]->ry() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWN) {
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->y() > map->i->item1LeftPositions[var]->y() + 24) || map->i->item1LeftPositions[var - 1]->x() != map->i->item1LeftPositions[var]->x()){
                map->i->item1LeftPositions[var]->ry() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHT) {
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() > map->i->item1LeftPositions[var]->x() + 24) || map->i->item1LeftPositions[var - 1]->y() != map->i->item1LeftPositions[var]->y()){
                map->i->item1LeftPositions[var]->rx() += 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFT || (x%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFT)) {
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() < map->i->item1LeftPositions[var]->x() - 24) || map->i->item1LeftPositions[var - 1]->y() != map->i->item1LeftPositions[var]->y()){
                map->i->item1LeftPositions[var]->rx() -= 4;
                map->i->update();
                //qDebug() << "2";
            }
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() > map->i->item1LeftPositions[var]->x() + 24) || map->i->item1LeftPositions[var - 1]->y() < map->i->item1LeftPositions[var]->y() - 24) {
                map->i->item1LeftPositions[var]->ry() -= 2;
                map->i->item1LeftPositions[var]->rx() += 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 10) {
                map->i->item1LeftPositions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_UPLEFT || (y%40 == 0 && map->buttons[30 * (y/40 - 1) + x/40]->IS_PASS_UPLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() < map->i->item1LeftPositions[var]->x() - 24) || map->i->item1LeftPositions[var - 1]->y() < map->i->item1LeftPositions[var]->y() - 24) {
                map->i->item1LeftPositions[var]->ry() -= 2;
                map->i->item1LeftPositions[var]->rx() -= 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 10) {
                map->i->item1LeftPositions[var]->ry() = y0 - 30;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNLEFT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNLEFT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() < map->i->item1LeftPositions[var]->x() - 24) || map->i->item1LeftPositions[var - 1]->y() > map->i->item1LeftPositions[var]->y() + 24) {
                map->i->item1LeftPositions[var]->ry() += 2;
                map->i->item1LeftPositions[var]->rx() -= 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 10) {
                map->i->item1LeftPositions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_DOWNRIGHT || (y%40 == 0 && map->buttons[30 * (y/40 + 1) + x/40]->IS_PASS_DOWNRIGHT)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() > map->i->item1LeftPositions[var]->x() + 24) || map->i->item1LeftPositions[var - 1]->y() > map->i->item1LeftPositions[var]->y() + 24) {
                map->i->item1LeftPositions[var]->ry() += 2;
                map->i->item1LeftPositions[var]->rx() += 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 10) {
                map->i->item1LeftPositions[var]->ry() = y0 + 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTUP) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() > map->i->item1LeftPositions[var]->x() + 24) || map->i->item1LeftPositions[var - 1]->y() < map->i->item1LeftPositions[var]->y() - 24) {
                map->i->item1LeftPositions[var]->ry() -= 2;
                map->i->item1LeftPositions[var]->rx() += 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 + 10) {
                map->i->item1LeftPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_RIGHTDOWN) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() > map->i->item1LeftPositions[var]->x() + 24) || map->i->item1LeftPositions[var - 1]->y() > map->i->item1LeftPositions[var]->y() + 24) {
                map->i->item1LeftPositions[var]->ry() += 2;
                map->i->item1LeftPositions[var]->rx() += 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 + 10) {
                map->i->item1LeftPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTUP || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40) * 40;
            } else {
                x0 = x;
                y0 = (y/40) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() < map->i->item1LeftPositions[var]->x() - 24) || map->i->item1LeftPositions[var - 1]->y() < map->i->item1LeftPositions[var]->y() - 24) {
                map->i->item1LeftPositions[var]->ry() -= 2;
                map->i->item1LeftPositions[var]->rx() -= 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 30) {
                map->i->item1LeftPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
        if(map->buttons[30 * (y/40) + x/40]->IS_PASS_LEFTDOWN || (y%40 == 0 && map->buttons[30 * (y/40) + x/40 - 1]->IS_PASS_LEFTUP)) {
            int x0, y0;
            if(y%40 == 0){
                x0 = (x/40 + 1) * 40;
                y0 = y;
            } else if(x%40 != 0){
                x0 = (x/40 + 1) * 40;
                y0 = (y/40 + 1) * 40;
            } else {
                x0 = x;
                y0 = (y/40 + 1) * 40;
            }
            if(var == 0 || (map->i->item1LeftPositions[var - 1]->x() < map->i->item1LeftPositions[var]->x() - 24) || map->i->item1LeftPositions[var - 1]->y() > map->i->item1LeftPositions[var]->y() + 24) {
                map->i->item1LeftPositions[var]->ry() += 2;
                map->i->item1LeftPositions[var]->rx() -= 2;
            }
            if(map->i->item1LeftPositions[var]->x() == x0 - 30) {
                map->i->item1LeftPositions[var]->ry() = y0 - 10;
            }
            map->i->update();
        }
    }
}

void MainWindow::levelup1() {
    if(t_1 > 1000 && coinnum >= 100) {
        t_1 -= 200;
        timer1->stop();
        timer1->start(t_1);
        coinnum -= 100;
    }
}

void MainWindow::levelup2() {
    if(t_2 > 25 && coinnum >= 100) {
        t_2 -= 5;
        timer2->stop();
        timer2->start(t_2);
        coinnum -= 100;
    }
}

void MainWindow::levelup3() {
    if(t_3 > 250 && coinnum >= 100) {
        t_3 -= 50;
        timer3->stop();
        timer3->start(t_3);
        coinnum -= 100;
    }
}

void MainWindow::levelup4() {
    if(coinnum >= 100) {
        map->center_imin -= 40;
        map->center_jmin -= 40;
        map->length += 80;
        coinnum -= 100;
        map->mapupdate();
    }
}

void MainWindow::levelup5() {
    if(coinnum >= 50) {
        coinnum -= 50;
        value++;
    }
}
