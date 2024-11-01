#include "openwidget.h"
#include <QApplication>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenWidget b;
    QMediaPlayer * player = new QMediaPlayer;

    b.resize(1200, 800);
    b.show();
    player->setSource(QUrl::fromLocalFile("C:/Users/72802/Desktop/project/ShapeZ/1.mp3"));
    player->play();
    return a.exec();
}
