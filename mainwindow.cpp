#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>

#include "Run_GMT_CMD_thread.h" // 多线程。用新线程运行gmt绘图，避免主界面卡死

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_gmt_cmd(QString cmd){
    waiting_thread_ui = new waiting_thread; //将类指针实例化
    waiting_thread_ui->exec(); //显示窗口， 非阻塞方式

    Run_GMT_CMD_thread *t = new Run_GMT_CMD_thread(); // 新建线程
    t->setarg(cmd);
    t->start();

    //t->quit();
    t->wait();
    //delete t;

}

void MainWindow::on_new_PS_file_clicked()
{
    new_ps_file_ui = new new_ps_file; //将类指针实例化
    new_ps_file_ui->exec(); //显示窗口， 阻塞方式

    ui->cmd_list->clear(); // 清除命令历史列表
    QString cmd = new_ps_file_ui->send_gmt_cmd(); // 获取第一条命令，建立空白画布
    ui->cmd_list->addItem(cmd); // 将第一条命令添加到列表中

    run_gmt_cmd(cmd);
    //cout << new_ps_file_ui->send_gmt_cmd().toUtf8().constData() << endl;
}
