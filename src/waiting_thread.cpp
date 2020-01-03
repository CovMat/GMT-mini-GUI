#include "waiting_thread.h"
#include "ui_waiting_thread.h"

#include <iostream>

waiting_thread::waiting_thread(QWidget *parent, QString S) :
    QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    cmd(S),
    ui(new Ui::waiting_thread)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("请等待GMT绘图 ……");
    ui->gmt_cmd->setText(cmd);

    /*开启一条多线程*/
    firstThread = new QThread; // 实例化新线程
    t = new Run_GMT_CMD(cmd);  // 实例化要在新线程中运行的工作代码
    t->moveToThread(firstThread); // 将工作代码移动到新线程中
    connect(firstThread,SIGNAL(finished()),t,SLOT(deleteLater())); // 线程的终止信号，连接到工作代码的deleteLater槽函数
    connect(firstThread,SIGNAL(started()),t,SLOT(dowork())); // 线程的启动信号，连接到工作代码的槽函数。这样线程启动的时候，就自动开始执行工作代码
    connect(t,SIGNAL(close_ready()),this,SLOT(normally_exit())); // 工作代码的结束信号，连接到本窗口的正常退出函数
    firstThread->start();

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    timer->start(100);

}

waiting_thread::~waiting_thread()
{
    delete ui;
}

void waiting_thread::normally_exit()
{
    // 正常退出代码
    if(firstThread->isRunning())
    {
        firstThread->quit();  //退出事件循环
        firstThread->wait();  //释放线程槽函数资源
    }
    exit_code = 0; // 正常退出
    this->close(); // 关闭窗口
}

void waiting_thread::on_stop_thread_clicked()
{
    // 强制退出代码
    if(firstThread->isRunning())
    {
        firstThread->quit();  //退出事件循环
        firstThread->wait();  //释放线程槽函数资源
    }

    exit_code = 1; // 强制终止
    this->close(); // 关闭窗口
}

void waiting_thread::updateUI(){
    QCoreApplication::processEvents();//避免界面冻结
}
