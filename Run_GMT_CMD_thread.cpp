#include <stdlib.h>
#include "Run_GMT_CMD_thread.h"


#include<windows.h>

// 多线程
Run_GMT_CMD_thread::Run_GMT_CMD_thread(QObject *parent) :
    QThread(parent)
{}

void Run_GMT_CMD_thread::run(){
    system(cmd.toUtf8().constData());
    long long i,j=0;

    for(i=0;i<999999999999;i++){
        j++;
    }
}
