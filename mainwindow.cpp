#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>

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

void MainWindow::on_new_PS_file_clicked()
{
    new_ps_file_ui = new new_ps_file; //将类指针实例化
    new_ps_file_ui->exec(); //显示窗口， 阻塞方式

    QString cmd = new_ps_file_ui->send_gmt_cmd(); // 获取第一条命令，建立空白画布

    if (cmd.isEmpty())
        return;

    waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->clear(); // 清除命令历史列表
        ui->cmd_list->addItem(cmd); // 将第一条命令添加到列表中
    }
}

void MainWindow::on_pscoast_clicked()
{
    GMT_pscoast_ui = new GMT_pscoast;
    GMT_pscoast_ui->exec();
}
