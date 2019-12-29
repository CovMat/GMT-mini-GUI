#include <iostream>
#include <QProcess>
#include "Run_GMT_CMD.h"

Run_GMT_CMD::Run_GMT_CMD(QString S) :
    cmd(S)
{}

void Run_GMT_CMD::dowork(){
    QProcess::execute(cmd);
    emit close_ready();
}
