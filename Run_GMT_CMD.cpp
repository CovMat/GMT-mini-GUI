#include <QtGlobal>
#include <QProcess>
#include <stdlib.h>
#include <stdio.h>
#include "Run_GMT_CMD.h"

Run_GMT_CMD::Run_GMT_CMD(QString S) :
    cmd(S)
{}

void Run_GMT_CMD::dowork(){
    #if defined(Q_OS_WIN32)
        system(cmd.toUtf8().constData());
    #else
        QProcess::execute(cmd);
    #endif
    /*
    QProcess *pro = new QProcess;
    pro->start(cmd);
    pro->waitForFinished();
    pro->close();
    */
    emit close_ready();
}
