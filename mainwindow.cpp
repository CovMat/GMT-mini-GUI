#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>
#include <QColor>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    psfname = ""; // 清空初始化ps文件文件名
    cmd_num = 0; // 命令数目清零
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 自定义函数，用于设置各个GMT绘图按钮是否有效
void MainWindow::set_gmt_button_enable(bool flag){
    ui->pscoast->setEnabled(flag);
    ui->psbasemap->setEnabled(flag);

    ui->endps->setEnabled(flag);

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
        cmd_num = 1; //命令初始化
        psfname = new_ps_file_ui->send_ps_fname(); // 获取文件名

        // 将各个绘图按钮有效化
        set_gmt_button_enable(true);
    }
}

void MainWindow::on_pscoast_clicked()
{
    GMT_pscoast_ui = new GMT_pscoast(this, psfname); // 将文件名传给pscoast对话框
    GMT_pscoast_ui->exec();

    QString cmd = GMT_pscoast_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
    }
}

void MainWindow::on_endps_clicked()
{
    QString cmd = "gmt psxy -JX1/1 -R0/1/0/1 -T -O >> "+psfname;
    waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中

        // 将各个绘图按钮无效化
        set_gmt_button_enable(false);
        // 三个撤销按钮无效化
        ui->undo->setEnabled(false);
        ui->redo->setEnabled(false);
        ui->undo_confirm->setEnabled(false);
    }

}

void MainWindow::on_undo_clicked()
{
    if (cmd_num<=1)
        return;
    ui->cmd_list->item(cmd_num-1)->setForeground(QColor(210,210,210));
    cmd_num--;
    // 将各个绘图按钮无效化
    set_gmt_button_enable(false);
    // 将确认按钮有效化
    ui->undo_confirm->setEnabled(true);
}

void MainWindow::on_redo_clicked()
{
    if (ui->cmd_list->count() == 1)
        return;
    if (cmd_num == ui->cmd_list->count()) // 如果已经恢复到头了，就退出
        return;
    ui->cmd_list->item(cmd_num)->setForeground(QColor(0,0,0));
    cmd_num++;
    // 如果全部命令都已经恢复，则各个绘图按钮有效化,将确认按钮无效化
    if (cmd_num == ui->cmd_list->count()){
        set_gmt_button_enable(true);
        ui->undo_confirm->setEnabled(false);
    }
}

void MainWindow::on_undo_confirm_clicked()
{
    // 保存第 0 ~ cmd_num-1 条命令
    QString tmp_list[1024];
    int i;
    for( i = 0; i < cmd_num; i++){
        tmp_list[i] = ui->cmd_list->item(i)->text();
    }
    //
    ui->cmd_list->clear(); // 清除命令历史列表
    // 重头开始执行
    int tmp_cmd_num = 0;
    for( i = 0; i < cmd_num; i++ ){
        waiting_thread_ui = new waiting_thread(this, tmp_list[i]); //将类指针实例化，创建对话框，同时将cmd传给新对话款
        waiting_thread_ui->exec(); //显示窗口， 阻塞方式
        if (waiting_thread_ui->send_exit_code() == 1 ) //如果中途中断，异常退出
        {
            break;
        }
        ui->cmd_list->addItem(tmp_list[i]);
        tmp_cmd_num++;
    }
    // 更新各个数据
    cmd_num = tmp_cmd_num;
    if (cmd_num == 0){ // 没有任何一条命令成功，回到初始状态
        // 将各个绘图按钮无效化
        set_gmt_button_enable(false);
    }else{ // 如果第一条命令成功了，则各个绘图按钮有效化
        // 将各个绘图按钮有效化
        set_gmt_button_enable(true);
    }
    // 将确认按钮无效化
    ui->undo_confirm->setEnabled(false);
}
