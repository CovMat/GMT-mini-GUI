#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //为了适应高分辨率屏幕必须加这个，否则缩放不正常
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
