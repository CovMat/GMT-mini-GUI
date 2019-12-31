#include <stdlib.h>
#include <stdio.h>
#include <QProcess>
#include "Run_GMT_CMD.h"

Run_GMT_CMD::Run_GMT_CMD(QString S) :
    cmd(S)
{}

void Run_GMT_CMD::dowork(){
    QProcess::execute(cmd);
    /*
    QProcess *pro = new QProcess;
    pro->start(cmd);
    pro->waitForFinished();
    pro->close();
    */
    emit close_ready();
}
