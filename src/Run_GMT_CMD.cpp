#include <QProcess>
#include <stdlib.h>
#include <stdio.h>
#include "Run_GMT_CMD.h"

Run_GMT_CMD::Run_GMT_CMD(QString S) :
    cmd(S)
{}

void Run_GMT_CMD::dowork(){
    /*
    #if defined(Q_OS_WIN32)
        system(cmd.toUtf8().constData());
    #else
        QProcess::execute(cmd);
    #endif
    */
    QString gmt_text = cmd.split(' ').at(0);
    if (gmt_text == "gmt"){
        QProcess::execute(cmd); // 如果是gmt命令，用QProcess运行。
    }
    else{
        system(cmd.toUtf8().constData()); // 如果是其他系统命令，使用system执行。 QProcess无法处理 “|” 这样的管道
    }

    emit close_ready();
}
