#include "mainwindow.h"

#include <QApplication>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //为了适应高分辨率屏幕必须加这个，否则缩放不正常
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFont font = a.font();
    #if defined(Q_OS_WIN)
        font.setPointSize(8);//字体大小
        font.setFamily("Microsoft YaHei");
    #elif defined(Q_OS_MACOS)
        font.setPointSize(8);//字体大小
        font.setFamily("PingFang SC");
    #else
        font.setPointSize(8);//字体大小
        font.setFamily("WenQuanYi Micro Hei");
    #endif
    a.setFont(font);

    return a.exec();
}
