#include "map.h"

Map::Map(QWidget *parent)
    : QWidget{parent}, length(160), center_imin(520), center_jmin(320)
{
    i = new itemwidget(this);
    for (int j = 0; j < 20; ++j) {
        for (int i = 0; i < 30; ++i) {
            if(i >= 4 && i <= 8 && j >= 13 && j <= 17){
                MapPushButton *btn = new MapPushButton;
                btn->setParent(this);
                btn->resize(40, 40);
                btn->move(40 * i, 40 * j);
                btn->setIcon(QIcon(":/map/map2.png"));
                btn->setIconSize(QSize(40, 40));
                buttons.push_back(btn);
                //TODO 为连接准备
            } else if(i >= 13 && i <= 16 && j >= 8 && j <= 11){
                MapPushButton *btn = new MapPushButton;
                btn->setParent(this);
                btn->resize(40, 40);
                btn->move(40 * i, 40 * j);
                btn->setIcon(QIcon(":/map/map3.png"));
                btn->setIconSize(QSize(40, 40));
                buttons.push_back(btn);
                //TODO 为连接准备
            } else if(i >= 23 && i <= 27 && j >= 2 && j <= 6){
                MapPushButton *btn = new MapPushButton;
                btn->setParent(this);
                btn->resize(40, 40);
                btn->move(40 * i, 40 * j);
                btn->setIcon(QIcon(":/map/map4.png"));
                btn->setIconSize(QSize(40, 40));
                buttons.push_back(btn);
                //TODO 为连接准备
            } else {
                MapPushButton *btn = new MapPushButton;
                btn->setParent(this);
                btn->resize(40, 40);
                btn->move(40 * i, 40 * j);
                btn->setIcon(QIcon(":/map/map1.png"));
                btn->setIconSize(QSize(40, 40));
                buttons.push_back(btn);
                //TODO 为连接准备
            }
        }
    }
}

void Map::mapupdate() {
    for (int var = 0; var < buttons.size(); ++var) {
        if(buttons[var]->IS_CUT_DOWN_1) {
            buttons[var]->setIcon(QIcon(":/map/cutdown1.png"));
        } else if(buttons[var]->IS_CUT_DOWN_2) {
            buttons[var]->setIcon(QIcon(":/map/cutdown2.png"));
        } else if(buttons[var]->IS_CUT_LEFT_1) {
            buttons[var]->setIcon(QIcon(":/map/cutleft1.png"));
        } else if(buttons[var]->IS_CUT_LEFT_2) {
            buttons[var]->setIcon(QIcon(":/map/cutleft2.png"));
        } else if(buttons[var]->IS_CUT_RIGHT_1) {
            buttons[var]->setIcon(QIcon(":/map/cutright1.png"));
        } else if(buttons[var]->IS_CUT_RIGHT_2) {
            buttons[var]->setIcon(QIcon(":/map/cutright2.png"));
        } else if(buttons[var]->IS_CUT_UP_1) {
            buttons[var]->setIcon(QIcon(":/map/cutup1.png"));
        } else if(buttons[var]->IS_CUT_UP_2) {
            buttons[var]->setIcon(QIcon(":/map/cutup2.png"));
        } else if(buttons[var]->IS_DIG_DOWN) {
            if(buttons[var]->x() >= 160 && buttons[var]->x() <= 320 && buttons[var]->y() >= 520 && buttons[var]->y() <= 680) {
               buttons[var]->setIcon(QIcon(":/map/digdown2.png"));
            } else if(buttons[var]->x() >= 920 && buttons[var]->x() <= 1080 && buttons[var]->y() >= 80 && buttons[var]->y() <= 240) {
               buttons[var]->setIcon(QIcon(":/map/digdown3.png"));
            }else {
                buttons[var]->setIcon(QIcon(":/map/digdown1.png"));
            }
        } else if(buttons[var]->IS_DIG_UP) {
            if(buttons[var]->x() >= 160 && buttons[var]->x() <= 320 && buttons[var]->y() >= 520 && buttons[var]->y() <= 680) {
                buttons[var]->setIcon(QIcon(":/map/digup2.png"));
            } else if(buttons[var]->x() >= 920 && buttons[var]->x() <= 1080 && buttons[var]->y() >= 80 && buttons[var]->y() <= 240) {
                buttons[var]->setIcon(QIcon(":/map/digup3.png"));
            }else {
                buttons[var]->setIcon(QIcon(":/map/digup1.png"));
            }
        } else if(buttons[var]->IS_DIG_RIGHT) {
            if(buttons[var]->x() >= 160 && buttons[var]->x() <= 320 && buttons[var]->y() >= 520 && buttons[var]->y() <= 680) {
                buttons[var]->setIcon(QIcon(":/map/digright2.png"));
            } else if(buttons[var]->x() >= 920 && buttons[var]->x() <= 1080 && buttons[var]->y() >= 80 && buttons[var]->y() <= 240) {
                buttons[var]->setIcon(QIcon(":/map/digright3.png"));
            }else {
                buttons[var]->setIcon(QIcon(":/map/digright1.png"));
            }
        } else if(buttons[var]->IS_DIG_LEFT) {
            if(buttons[var]->x() >= 160 && buttons[var]->x() <= 320 && buttons[var]->y() >= 520 && buttons[var]->y() <= 680) {
                buttons[var]->setIcon(QIcon(":/map/digleft2.png"));
            } else if(buttons[var]->x() >= 920 && buttons[var]->x() <= 1080 && buttons[var]->y() >= 80 && buttons[var]->y() <= 240) {
                buttons[var]->setIcon(QIcon(":/map/digleft3.png"));
            }else {
                buttons[var]->setIcon(QIcon(":/map/digleft1.png"));
            }
        } else if(buttons[var]->IS_PASS_DOWN) {
            buttons[var]->setIcon(QIcon(":/map/passdown.png"));
        } else if(buttons[var]->IS_PASS_DOWNLEFT) {
            buttons[var]->setIcon(QIcon(":/map/passdownleft.png"));
        } else if(buttons[var]->IS_PASS_DOWNRIGHT) {
            buttons[var]->setIcon(QIcon(":/map/passdownright.png"));
        } else if(buttons[var]->IS_PASS_LEFT) {
            buttons[var]->setIcon(QIcon(":/map/passleft.png"));
        } else if(buttons[var]->IS_PASS_LEFTDOWN) {
            buttons[var]->setIcon(QIcon(":/map/passleftdown.png"));
        } else if(buttons[var]->IS_PASS_LEFTUP) {
            buttons[var]->setIcon(QIcon(":/map/passleftup.png"));
        } else if(buttons[var]->IS_PASS_RIGHT) {
            buttons[var]->setIcon(QIcon(":/map/passright.png"));
        } else if(buttons[var]->IS_PASS_RIGHTDOWN) {
            buttons[var]->setIcon(QIcon(":/map/passrightdown.png"));
        } else if(buttons[var]->IS_PASS_RIGHTUP) {
            buttons[var]->setIcon(QIcon(":/map/passrightup.png"));
        } else if(buttons[var]->IS_PASS_UP) {
            buttons[var]->setIcon(QIcon(":/map/passup.png"));
        } else if(buttons[var]->IS_PASS_UPLEFT) {
            buttons[var]->setIcon(QIcon(":/map/passupleft.png"));
        } else if(buttons[var]->IS_PASS_UPRIGHT) {
            buttons[var]->setIcon(QIcon(":/map/passupright.png"));
        } else if(buttons[var]->x() >= center_imin && buttons[var]->x() <= center_imin + length
                   && buttons[var]->y() >= center_jmin && buttons[var]->y() <= center_jmin + length) {
            buttons[var]->setIcon(QIcon(":/map/map3.png"));
        }

    }
}
